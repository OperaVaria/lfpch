# Meson build file for the "Lightning-Fast Password Check" project

# Project call
project('lfpch', 'c',
        version : '0.0.2',
        license : 'GPL-3.0-only',
        license_files : 'COPYING.md',
        default_options : ['buildtype=release', 'c_std=gnu17', 'c_args=-mrdseed']
        )

# Only build if the target CPU is x86:
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

# Project directories
subdir('src')
subdir('resources')
inc = include_directories('include')

# Install directories
if host_machine.system() == 'windows'
  bin_dir = get_option('prefix') / 'Tools' / 'lfpch'
  data_dir = bin_dir / 'resources'
  license_dir = bin_dir / 'license'
  icon_dir = data_dir
  desktop_dir = data_dir
else
  bin_dir = '/usr' / 'bin'
  share_dir = '/usr' / 'share'
  data_dir =  share_dir / 'lfpch'
  license_dir = share_dir / 'doc' / 'lfpch'
  icon_dir = share_dir / 'icons'
  desktop_dir = share_dir / 'applications'
endif

# Windows resource file compilation
if host_machine.system() == 'windows'
  windows = import('windows')
  src += windows.compile_resources('resources/lfpch.rc')
endif

# Executable
executable('lfpch',
           sources : src,
           include_directories: inc,
           link_args : ['-s'],
           dependencies : deps,
           win_subsystem : 'windows',
           install : true,
           install_dir: bin_dir
           )

# Install
install_data('resources/styles.css', install_dir : data_dir)
install_data('COPYING.md', install_dir : license_dir)
if host_machine.system() == 'windows'
  install_data('resources/icons/ico/lfpch.ico', install_dir : icon_dir)
else
  install_data('resources/lfpch.desktop', install_dir : desktop_dir)
  install_subdir('resources/icons/hicolor', install_dir : icon_dir)
endif

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
