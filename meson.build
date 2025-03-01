project('vissort', 'cpp')

cxx = meson.get_compiler('cpp')

cpp_args = []
link_args = []
name_suffix = []
dependencies = []

# Raylib config
cmake = import('cmake')
raylib_opts = cmake.subproject_options()
raylib_opts.set_install(false)
raylib_opts.add_cmake_defines(
    {
        'BUILD_EXAMPLES': 'OFF',
        'PLATFORM': 'Desktop',
    },
)
raylib_subproject = cmake.subproject('raylib', options: raylib_opts)
dependencies += raylib_subproject.dependency('raylib')

if host_machine.system() == 'windows'
    dependencies += [cxx.find_library('winmm')]
elif host_machine.system() == 'linux'
    dependencies += [cxx.find_library('m'), cxx.find_library('dl')]
endif

inc_dir = include_directories('include')

sources = files('src/main.cpp')

executable(
    meson.project_name(),
    sources: sources,
    cpp_args: cpp_args,
    dependencies: dependencies,
    include_directories: inc_dir,
    link_args: link_args,
    name_suffix: name_suffix,
)