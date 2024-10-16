# Meson build file for the "Lightning-Fast Password Check" project

# Project call
project('lfpch', 'c',
        version : '1.0.0',
        license : 'GPL-3.0-only',
        license_files : 'COPYING.md',
        default_options : ['buildtype=release', 'c_std=gnu17', 'c_args=-mrdseed']
        )

# Only build if the target CPU is x86
is_x86 = host_machine.cpu_family().startswith('x86')
if not is_x86
  error('This application currently only supports x86 architecture.')
endif

# Dependencies
glib_dep = dependency('glib-2.0')
gtk4_dep = dependency('gtk4')
libcrypto_dep = dependency('libcrypto')
libcurl_dep = dependency('libcurl')
deps = [glib_dep, gtk4_dep, libcrypto_dep, libcurl_dep]

# Directories
subdir('src')
subdir('resources')
inc = include_directories('include')
if host_machine.system() == 'windows'
  inst_dir = get_option('prefix') / 'Tools' / 'lfpch'
else
  inst_dir = fs.expanduser('~/lfpch')
endif

# Executable
executable('lfpch',
           sources : src,
           include_directories: inc,
           dependencies : deps,
           win_subsystem : 'windows',
           install : true,
           install_dir: inst_dir
           )

# Install
install_subdir('resources', install_dir : inst_dir)
install_data('COPYING.md', install_dir : inst_dir / 'license')

# Tests
test('connection', executable('conn_test',
                              sources: ['tests/conn_test.c', 'src/request.c'],
                              include_directories: inc,
                              dependencies : deps
                              ))

test('DRNG', executable('drng_test',
                        sources: ['tests/drng_test.c'],
                        include_directories: inc,
                        dependencies : deps
                        ))

test('generator', executable('gen_test',
                              sources: ['tests/gen_test.c', 'src/checker.c', 'src/generator.c', 'src/hashing.c', 'src/request.c'],
                              include_directories: inc,
                              dependencies : deps
                              ))
