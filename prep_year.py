# prep_year.py

import argparse
import os


def create_folders(
        year):
    inc_dir = os.path.join(year, 'inc')
    src_dir = os.path.join(year, 'src')
    subprojects_dir = os.path.join(year, 'subprojects')

    paths_to_make = [year, inc_dir, src_dir, subprojects_dir]

    for path in paths_to_make:
        if not os.path.exists(path):
            os.mkdir(path)

    utility_link_source = os.path.join('..', '..', 'utility')
    utility_link_target = os.path.join(year, 'subprojects', 'adventUtility')

    if not os.path.exists(utility_link_target):
        os.symlink(utility_link_source, utility_link_target)


def create_meson_build_file(
        year):
    filename = os.path.join(year, 'meson.build')

    if os.path.exists(filename):
        return

    with open(filename, 'w') as f:
        f.write(f"project('advent{year}', 'cpp', default_options: [ 'default_library=static', 'warning_level=1', 'werror=false', 'cpp_std=c++17' ], version:'0.0.1')\n\n")

        f.write("inc_dirs = include_directories('inc')\n\n")

        f.write(f"source=[\n\t'src/lib{year}.cpp',\n")

        for d in range(25):
            f.write(f"\t'src/{d + 1:02}.cpp',\n")

        f.write("]\n\n")

        f.write("adventUtility = subproject('adventUtility')\n")
        f.write("adventUtility_dep = adventUtility.get_variable('adventUtility_dep')\n\n")

        f.write(f"advent{year} = library(\n")
        f.write(f"\t'advent{year}',\n")
        f.write("\tsource,\n")
        f.write("\tinclude_directories:inc_dirs,\n")
        f.write("\tdependencies:[\n")
        f.write("\t\tadventUtility_dep,\n")
        f.write("\t],\n")
        f.write(")\n\n")

        f.write(f"advent{year}_dep = declare_dependency(\n")
        f.write("\tinclude_directories:inc_dirs,\n")
        f.write(f"\tlink_with:advent{year},\n")
        f.write(")\n")

def write_main_header(
        year):
    with open(os.path.join(year, 'inc', f'lib{year}.h'), 'w') as f:
        f.write(f'#ifndef ADVENT_{year}_H\n')
        f.write(f'#define ADVENT_{year}_H\n\n')
        f.write('#include <string>\n\n')
        f.write('#include "adventTypedef.h"\n\n\n')
        f.write(f'namespace advent {{ namespace y{year}\n')
        f.write('{\n')
        f.write('\tstd::pair<adventFunctor, adventFunctor> getDay(\n')
        f.write('\t\t\tconst std::string& day);\n')
        f.write('} }\n\n')
        f.write('#endif\n')


def write_day_header(
        year,
        day):
    filename = os.path.join(year, 'inc', f'{day:02}.h')

    if os.path.exists(filename):
        return

    with open(filename, 'w') as f:
        f.write(f'#ifndef ADVENT_{year}_{day:02}_H\n')
        f.write(f'#define ADVENT_{year}_{day:02}_H\n\n')
        f.write('#include "adventTypedef.h"\n\n\n')
        f.write(f'namespace advent {{ namespace y{year} {{ namespace d{day:02}\n')
        f.write('{\n')
        f.write('\tstd::pair<adventFunctor, adventFunctor> getParts();\n')
        f.write('} } }\n\n')
        f.write('#endif\n')

def write_headers(
        year):
    write_main_header(year)

    for d in range(25):
        write_day_header(year, d + 1)


def write_main_source(
        year):
    filename = os.path.join(year, 'src', f'lib{year}.cpp')

    with open(filename, 'w') as f:
        f.write(f'#include "lib{year}.h"\n\n')
        
        for d in range(25):
            f.write(f'#include "{d + 1:02}.h"\n')

        f.write('\n#include <stdexcept>\n\n')
        
        f.write(f'namespace advent {{ namespace y{year}\n')
        f.write('{\n')
        f.write('\tstd::pair<adventFunctor, adventFunctor> getDay(\n')
        f.write('\t\t\tconst std::string& day)\n')
        f.write('\t{\n')
        
        for d in range(25):
            if d < 10:
                f.write(f'\t\tif ("{d + 1}" == day || "{d + 1:02}" == day)\n')
            else:
                f.write(f'\t\tif ("{d + 1}" == day)\n')
            f.write(f'\t\t\treturn d{d + 1:02}::getParts();\n')

        f.write('\n\t\tthrow std::invalid_argument("Encountered unparseable day");\n')
        f.write('\t}\n')
        f.write('} }\n')


def write_day_source(
        year,
        day):
    filename = os.path.join(year, 'src', f'{day:02}.cpp')

    if os.path.exists(filename):
        return

    with open(filename, 'w') as f:
        f.write(f'#include "{day:02}.h"\n\n\n')
        f.write(f'namespace advent {{ namespace y{year} {{ namespace d{day:02}\n')
        f.write('{\n')
        f.write('\tstd::string partOne(\n')
        f.write('\t\t\tconst std::string& inFilename)\n')
        f.write('\t{\n')
        f.write('\t\treturn "nonimpl";\n')
        f.write('\t}\n\n')
        f.write('\tstd::string partTwo(\n')
        f.write('\t\t\tconst std::string& inFilename)\n')
        f.write('\t{\n')
        f.write('\t\treturn "nonimpl";\n')
        f.write('\t}\n\n')
        f.write('\tstd::pair<adventFunctor, adventFunctor> getParts()\n')
        f.write('\t{\n')
        f.write('\t\treturn { partOne, partTwo };\n')
        f.write('\t}\n')
        f.write('} } }\n')

def write_source(
        year):
    write_main_source(year)

    for d in range(25):
        write_day_source(year, d + 1)


def main(
        year):
    create_folders(year)
    create_meson_build_file(year)
    write_headers(year)
    write_source(year)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
            prog='prep_year.py',
            description='Setup folder structure for a year in this C++ AoC repo')

    parser.add_argument('year')

    args = parser.parse_args()

    main(args.year)

