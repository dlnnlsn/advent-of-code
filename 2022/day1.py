#!/usr/bin/env python3

current_elf = 0
max_elf = 0

while True:
    try:
        calories = input()
        if calories == "":
            max_elf = max(max_elf, current_elf)
            current_elf = 0
        else:
            current_elf += int(calories)
    except EOFError:
        max_elf = max(max_elf, current_elf)
        break

print(max_elf)
