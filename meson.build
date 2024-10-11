project('advent-of-code', 'cpp', default_options: ['default_library=static', 'warning_level=1', 'werror=false', 'cpp_std=c++17', ], version:'0.0.1')

dir_base = meson.current_source_dir()

dir_install = join_paths(dir_base, 'result')

argp_dep = dependency('argparse')

inc_dirs = include_directories(
  'inc',
)

source = [
  'src/argumentParsing.cpp',
  'src/evaluator.cpp',
  'src/main.cpp'
]

advent2015 = subproject('advent2015')
advent2015_dep = advent2015.get_variable('advent2015_dep')

adventUtility = subproject('adventUtility')
adventUtility_dep = adventUtility.get_variable('adventUtility_dep')

openssl_dep = dependency('openssl')

executable(
  'advent',
  source,
  include_directories:inc_dirs,
  dependencies:[
    argp_dep,
    openssl_dep,
    advent2015_dep,
    adventUtility_dep,
  ],
  install:true,
  install_dir:dir_install
)

