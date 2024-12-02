# pull_input.py

import argparse
import os
import time

from aocd import get_data


def main(
        year,
        day):
    input_dir = 'input'

    if not os.path.exists(input_dir):
        os.mkdir(input_dir)

    filename = f'{year}_{day:02}'
    filename = os.path.join(input_dir, filename)
    
    if os.path.exists(filename):
        print(f'skipping {year} {day}. Input file exists')

        return


    print(f'pulling {year} {day}')

    data = get_data(day=day, year=year)

    with open(filename, 'w') as f:
        f.write(data)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
            prog='pull_input.py',
            description='Pull input for a year in this C++ AoC repo')

    parser.add_argument('year')
    parser.add_argument('day')

    args = parser.parse_args()

    main(int(args.year), int(args.day))

