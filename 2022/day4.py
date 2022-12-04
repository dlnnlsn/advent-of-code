#!/usr/bin/env python3

count = 0

while True:
    try:
        first_elf, second_elf = input().split(',')
        first_start, first_end = map(int, first_elf.split('-'))
        second_start, second_end = map(int, second_elf.split('-'))

        if second_start <= first_start <= second_end:
            count += 1
        elif first_start <= second_start <= first_end:
            count += 1
    except EOFError:
        break

print(count)
