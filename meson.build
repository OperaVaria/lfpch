# Meson build file for the "Lightning-Fast Password Check" project
project('lfpch', 'c',
        version : '1.0.0',
        license : 'GPL3',
        default_options : ['buildtype=release', 'c_std=gnu17'])

# Only build if the target CPU is x86
is_x86 = host_machine.cpu_family().startswith('x86')
if not is_x86
  error('This application currently only supports x86 architecture.')
endif

# Compiler and linker arguments
extra_args = ['-mrdseed'] # rdseed for random generation.
extra_link_args = []
if host_machine.system() == 'windows'  
  extra_link_args += ['-mwindows'] # Add -mwindows on Windows.
endif

# Dependencies
gtk_dep = dependency('gtk4')
crypto_dep = dependency('libcrypto')
curl_dep = dependency('libcurl')

# Directories
subdir('src')
inc = include_directories('include')

# Executable
executable('lfpch',
           sources : src,
           include_directories: inc,
           dependencies : [gtk_dep, crypto_dep, curl_dep],
           c_args : extra_args,
           link_args : extra_link_args,
           win_subsystem : 'windows',
           install : true)

# Install files
install_data('COPYING.md', install_dir : get_option('datadir') / 'licenses' / 'lfpch')
install_data('resources/styles/lfpch.css', install_dir : get_option('datadir') / 'styles' / 'lfpch')

# Tests
test('generator', executable('gen_test', 'tests/gen_test.c'))
