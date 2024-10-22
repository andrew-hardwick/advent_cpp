project('advent2015', 'cpp', default_options: ['default_library=static', 'warning_level=1', 'werror=false', 'cpp_std=c++17', ], version:'0.0.1')

inc_dirs = include_directories('inc')

source = [
  'src/lib2015.cpp',
  'src/01.cpp',
  'src/02.cpp',
  'src/03.cpp',
  'src/04.cpp',
  'src/05.cpp',
  'src/06.cpp',
  'src/07.cpp',
  'src/08.cpp',
  'src/09.cpp',
  'src/10.cpp',
]

adventUtility = subproject('adventUtility')
adventUtility_dep = adventUtility.get_variable('adventUtility_dep')

advent2015 = library(
  'advent2015',
  source,
  include_directories:inc_dirs,
  dependencies:[adventUtility_dep]
)

advent2015_dep = declare_dependency(
  include_directories: inc_dirs,
  link_with: advent2015,
)
