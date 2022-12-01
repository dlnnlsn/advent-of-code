#!/usr/bin/env python3

current_elf = 0
top3 = [0, 0, 0]

while True:
    try:
        calories = input()
        if calories == "":
            top3 = list(sorted(top3 + [current_elf]))[1:]
            current_elf = 0
        else:
            current_elf += int(calories)
    except EOFError:
        top3 = list(sorted(top3 + [current_elf]))[1:]
        break

print(sum(top3))
