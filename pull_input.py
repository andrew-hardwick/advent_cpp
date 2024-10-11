# pull_input.py

import os
import time

from aocd import get_data


def main():
    input_dir = 'input'

    if not os.path.exists(input_dir):
        os.mkdir(input_dir)

    for year in range(2015, 2025):
        for day in range(1, 26):
            print(f'pulling {year} {day}')
            data = get_data(day=day, year=year)

            filename = f'{year}_{day:02}'
            filename = os.path.join(input_dir, filename)

            with open(filename, 'w') as f:
                f.write(data)

            time.sleep(1.5)

        print(f'year {year} complete')

if __name__ == '__main__':
    main()

