project('advent-of-code', 'cpp', default_options: ['default_library=static', 'warning_level=1', 'werror=false', 'cpp_std=c++17', ], version:'0.0.1')

dir_base = meson.current_source_dir()

dir_install = join_paths(dir_base, 'result')

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

advent2024 = subproject('advent2024')
advent2024_dep = advent2024.get_variable('advent2024_dep')

adventUtility = subproject('adventUtility')
adventUtility_dep = adventUtility.get_variable('adventUtility_dep')

argp_dep = dependency('argparse')
openssl_dep = dependency('openssl')

nlohmann_json = subproject('json')
nlohmann_json_dep = nlohmann_json.get_variable('nlohmann_json_dep')

executable(
  'advent',
  source,
  include_directories:inc_dirs,
  dependencies:[
    argp_dep,
    openssl_dep,
    nlohmann_json_dep,
    advent2015_dep,
    advent2024_dep,
    adventUtility_dep,
  ],
  install:true,
  install_dir:dir_install
)

