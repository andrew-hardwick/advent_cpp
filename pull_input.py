# pull_input.py

import argparse
import os
import time

from aocd import get_data


def main(
        year):
    input_dir = 'input'

    if not os.path.exists(input_dir):
        os.mkdir(input_dir)

    for day in range(1, 26):
        filename = f'{year}_{day:02}'
        filename = os.path.join(input_dir, filename)
        
        if os.path.exists(filename):
            print(f'skipping {year} {day}. Input file exists')

            continue;

        print(f'pulling {year} {day}')

        data = get_data(day=day, year=year)

        with open(filename, 'w') as f:
            f.write(data)

        time.sleep(1.5)

        print(f'year {year} complete')

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
            prog='pull_input.py',
            description='Pull input for a year in this C++ AoC repo')

    parser.add_argument('year')

    args = parser.parse_args()

    main(args.year)


