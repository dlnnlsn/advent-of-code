#!/usr/bin/env python3

def item_priority(item):
    if 'a' <= item <= 'z':
        return ord(item) - ord('a') + 1
    if 'A' <= item <= 'Z':
        return ord(item) - ord('A') + 27
    return 0


total = 0
elves_per_group = 3

while True:
    try:
        badges = set(input())
        for i in range(1, elves_per_group):
            elf = set(input())
            badges = badges.intersection(elf)
        total += sum(map(item_priority, badges))
    except EOFError:
        break

print(total)
