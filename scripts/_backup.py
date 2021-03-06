#!/usr/bin/python3
import argparse
import pathlib
import json
import pprint
import os
import subprocess

ARCH_DIR = pathlib.Path('arch').resolve()
BIN_DIR = pathlib.Path('bin').resolve()
BUILD_DIR = pathlib.Path('.build').resolve()
INCLUDE_DIR = pathlib.Path('include').resolve()
SRC_DIR = pathlib.Path('src').resolve()
CFLAGS = ['-Wall', '-std=c18'] # '-Wpedantic', '-Werror', '-Wextra', 
FLAGS = None
TARGETS = {}

def define_targets():
    c_src = detect_sources(SRC_DIR)
    src_map = {src_file : ([], []) for src_file in c_src}

    define_target(name='x86_64-pc-linux-gnu',
            cc='x86_64-pc-linux-gnu-gcc',
            out_filename='game',
            cflags=[*CFLAGS],
            bin_dir=BIN_DIR,
            include_dirs=[INCLUDE_DIR],
            src_map=src_map,
            libs=['SDL2', 'SDL2main'],
            symbols=[],
            flags=[])

    define_target(name='x86_64-w64-mingw32',
            cc='x86_64-w64-mingw32-gcc',
            out_filename='game.exe',
            cflags=[*CFLAGS],
            bin_dir=BIN_DIR,
            include_dirs=[INCLUDE_DIR],
            src_map=src_map,
            libs=['SDL2', 'SDL2main'], 
            symbols=['SDL_MAIN_HANDLED'],
            flags=[])

    define_target(name='i686-w64-mingw32',
            cc='i686-w64-mingw32-gcc',
            out_filename='game.exe',
            cflags=[*CFLAGS],
            bin_dir=BIN_DIR,
            include_dirs=[INCLUDE_DIR],
            src_map=src_map,
            libs=['SDL2', 'SDL2main'], 
            symbols=['SDL_MAIN_HANDLED'],
            flags=[])

def _log_paths(paths, **kwargs):
    pprint.pprint([str(path) for path in paths], **kwargs)

def log(*args, **kwargs):
    """OPTIONS:

    verbose: 1 or 0.
    log_options: kwargs for pprint.
    log_level: 'error', 'warning' or 'info', default is 'info'.
    """
    log_level = kwargs.get('log_level', 'info')
    if (not kwargs.get('verbose', 1)) or FLAGS.verbose or log_level != 'info':
        log_options = kwargs.get('log_options', {})
        print(f'{log_level.upper()}:')
        for arg in args:
            if isinstance(arg, str):
                print(arg)
            elif isinstance(arg, list) and len(arg) > 0 and isinstance(arg[0], pathlib.Path):
                _log_paths(arg, **log_options)
            else:
                pprint.pprint(arg, **log_options)

def filter_paths(paths, to_remove):
    return [path for path in paths if path not in to_remove]

def filter_dirs(paths, to_remove):
    files_to_remove = []
    for remove_dir in to_remove:
        files_to_remove.extend(detect_sources(remove_dir, file_extension=''))
    return filter_filepaths(paths, files_to_remove)

def ensure_dir_exists(path):
    path.mkdir(exist_ok=True)

def read_target_file(target_file_path):
    with open(target_file_path, 'r') as target_file:
        data = json.loads(target_file.read())
    return data

def write_target_file(target_file_path, name):
    target = TARGETS[name]
    data = {str(src_file.resolve()) : os.stat(str(src_file.resolve())).st_mtime for src_file in target['src_map'].keys()}
    log(f'Writing target file at {target_file_path} with:', data)
    with open(target_file_path, 'w') as target_file:
        target_file.write(json.dumps(data))

def define_target(name, cc, out_filename, cflags, bin_dir, include_dirs, src_map, libs, symbols, flags):
    """
    src_map: dict - keys are paths for source files, values are tuples with file-specific compiler flags and symbols.
    """
    TARGETS[name] = {'cc' : cc,
            'out_filename' : out_filename,
            'cflags' : cflags,
            'bin' : bin_dir,
            'include' : include_dirs,
            'src_map' : src_map,
            'lib' : libs,
            'def' : symbols,
            'flags' : flags}

    log(f'Target {name} defined:', TARGETS[name])

    target_file_path = BUILD_DIR.joinpath(f'{name}.json')
    if not target_file_path.exists():
        write_target_file(target_file_path, name)

def build_target(name, mode='partial'):
    """Ex:
    Say source filepath is src/some_dir/file_idk.c
    Its object file will be named src:some_dir:file_idk.o
    """
    log(f'Building target {name} with mode {mode}.')
    target = TARGETS[name]
    bin_dir = BIN_DIR.joinpath(name)
    ensure_dir_exists(bin_dir)
    target_file = BUILD_DIR.joinpath(f'{name}.json')

    if mode == 'full':
        to_compile, to_remove = compiler_files_full(name)
    elif mode == 'partial':
        to_compile, to_remove = compiler_files_partial(name)

    log('Compiling:', list(to_compile))
    log('Removing:', list(to_remove))

    commands = compiler_commands(to_compile, name)

    write_target_file(target_file, name)
    for obj_file in to_remove:
        obj_file.unlink()
    out = shell_inline('\n'.join([' '.join([str(word) for word in command]) for command in commands]))
    if out.returncode != 0:
        log('Critical error when compiling.', log_level='error')
        out.check_returncode()
    log('Compiled successfully.')
    object_files = detect_sources(bin_dir, file_extension='.o')
    log('Linking:', object_files)
    out = shell_inline(' '.join([str(word) for word in [target['cc'], '-o', bin_dir.joinpath(target['out_filename']), *object_files, *[f'-l{lib}' for lib in target['lib']]]]))
    if out.returncode != 0:
        log('Critical error when linking.', log_level='error')
        out.check_returncode()
    log('Linked successfully.')
    log(f'Executable produced at {bin_dir.joinpath(target["out_filename"])}.')

def compiler_files_full(name):
    return TARGETS[name]['src_map'].keys(), detect_sources(BIN_DIR.joinpath(name), file_extension='.o')

def compiler_files_partial(name):
    target = TARGETS[name]
    bin_dir = BIN_DIR.joinpath(name)
    obj_files = detect_sources(bin_dir, file_extension='.o')
    log('Detected object files:', obj_files)

    obj_names = {src_file : bin_dir.joinpath(str(src_file).replace('/', ':').replace('.c', '.o')) for src_file in target['src_map'].keys()}
    src_names = {obj_file : pathlib.Path(str(obj_file.name).replace(':', '/').replace('.o', '.c')) for obj_file in obj_files}
    exist = {src_name : obj_name for src_name, obj_name in obj_names.items() if obj_name.exists() and src_name.exists()}
    obj_nonexistant = {src_name : obj_name for src_name, obj_name in obj_names.items() if not obj_name.exists()}
    src_nonexistant = {obj_name : src_name for obj_name, src_name in src_names.items() if not src_name.exists()}
    log('Existant object & source files:', exist, 'Nonexistant object files:', obj_nonexistant, 'Nonexistant source files:', src_nonexistant)
    to_compile = []
    to_remove = []
    to_compile.extend(obj_nonexistant.keys())
    to_remove.extend(src_nonexistant.keys())

    target_file = BUILD_DIR.joinpath(f'{name}.json')
    old_data = read_target_file(target_file)

    for src, obj in exist.items():
        old_time = old_data[str(src)]
        new_time = os.stat(str(src)).st_mtime
        log(f'File {src} was modified at {new_time}, recorded time is {old_time}.')
        if  new_time != old_time:
            to_compile.append(src)
            to_remove.append(obj)

    return to_compile, to_remove

def compiler_commands(to_compile, name):
    target = TARGETS[name]
    bin_dir = BIN_DIR.joinpath(name)
    obj_names = {src_file : bin_dir.joinpath(str(src_file).replace('/', ':').replace('.c', '.o')) for src_file in to_compile}
    commands = []

    for src_file in to_compile:
        cflags = target['cflags']
        symbols = target['def']
        cflags.extend(target['src_map'][src_file][0])
        symbols.extend(target['src_map'][src_file][1])
        commands.append([target['cc'], src_file, '-c', '-o', obj_names[src_file], *cflags,
                *[f'-I{include_dir}' for include_dir in target['include']],
                *[f'-D{symbol}' for symbol in symbols]])

    return commands

def _detect_sources(src_dir, file_extension):
    src_files = []
    directories = []
    for path in src_dir.iterdir():
        if path.is_dir():
            directories.append(path.resolve())
        elif str(path).endswith(file_extension):
            src_files.append(path.resolve())

    return src_files, directories

def detect_sources(src_dir, file_extension='.c'):
    directories = [src_dir]
    src_files = []
    while len(directories) > 0:
        new_directories = []
        for dir_path in directories:
            new_files, new_dir_paths = _detect_sources(dir_path, file_extension)
            src_files.extend(new_files)
            new_directories.extend(new_dir_paths)
        directories = new_directories

    return src_files

def parse_args():
    parser = argparse.ArgumentParser(prog='build_game', description='Build game.')

    parser.add_argument('targets', nargs='+', help='Targets to build. Pass \'all\' to build all defined targets.')

    mode = parser.add_mutually_exclusive_group()
    mode.add_argument('-mp', '--partial', help='Build partially, i.e. only compile modified files. Default option.', dest='mode', action='store_const', const='partial', default='partial')
    mode.add_argument('-mf', '--full', help='Build fully, i.e. compile all files.', dest='mode', action='store_const', const='full')

    parser.add_argument('-v', '--verbose', action='store_true', help='Turn on verbosity.')
    parser.add_argument('-f', '--flags', help='Additional compiler flags.')

    args = parser.parse_args()

    if 'all' in args.targets:
        args.targets = list(TARGETS.keys())
    
    return args

def shell_exec(path, run_dir=pathlib.Path.cwd(), *args):
    old_dir = pathlib.Path.cwd()
    os.chdir(run_dir)
    log(f'Executing script at {path} in directory {run_dir} with arguments {args}.')
    out = subprocess.run([f'./{path}', *args], capture_output=True)
    if out.returncode != 0:
        log(f'Script exited with return code {out.returncode}.', log_level='warning')
    log(f'Script stdout:', out.stdout.decode(), 'Script stderr:', out.stderr.decode())
    os.chdir(old_dir)
    return out

def shell_inline(code, run_dir=pathlib.Path.cwd(), *args):
    with open('script.sh', 'w') as script:
        script.write(''.join(['#!/bin/bash\n', code]))
    script = pathlib.Path('script.sh')
    script.chmod(0o777)
    log(f'Executing inline shell script in directory {run_dir} with arguments {args}, script:', code)
    out = shell_exec(script, run_dir, *args)
    script.unlink()
    return out

def main():
    global FLAGS

    FLAGS = parse_args()
    define_targets()
    for dir_path in [ARCH_DIR, BIN_DIR, BUILD_DIR, INCLUDE_DIR, SRC_DIR]:
        ensure_dir_exists(dir_path)

    log('Building with options:', vars(FLAGS), verbose=0)
    log('Defined Targets:', list(TARGETS.keys()))

    for target in FLAGS.targets:
        build_target(target, mode=FLAGS.mode)
    
if __name__ == '__main__':
    main()
