project('advent2024', 'cpp', default_options: [ 'default_library=static', 'warning_level=1', 'werror=false', 'cpp_std=c++17' ], version:'0.0.1')

inc_dirs = include_directories('inc')

source=[
	'src/lib2024.cpp',
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
	'src/11.cpp',
	'src/12.cpp',
	'src/13.cpp',
	'src/14.cpp',
	'src/15.cpp',
	'src/16.cpp',
	'src/17.cpp',
	'src/18.cpp',
	'src/19.cpp',
	'src/20.cpp',
	'src/21.cpp',
	'src/22.cpp',
	'src/23.cpp',
	'src/24.cpp',
	'src/25.cpp',
]

adventUtility = subproject('adventUtility')
adventUtility_dep = adventUtility.get_variable('adventUtility_dep')

nlohmann_json = subproject('json')
nlohmann_json_dep = nlohmann_json.get_variable('nlohmann_json_dep')

advent2024 = library(
	'advent2024',
	source,
	include_directories:inc_dirs,
	dependencies:[
		adventUtility_dep,
    nlohmann_json_dep,
	],
)

advent2024_dep = declare_dependency(
	include_directories:inc_dirs,
	link_with:advent2024,
)
