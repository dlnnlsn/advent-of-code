#!/usr/bin/env python3

total = 0


def item_priority(item):
    if 'a' <= item <= 'z':
        return ord(item) - ord('a') + 1
    if 'A' <= item <= 'Z':
        return ord(item) - ord('A') + 27
    return 0


def process_rucksack(rucksack):
    left_compartment = set(rucksack[:len(rucksack)//2])
    right_compartment = set(rucksack[len(rucksack)//2:])
    overlap = right_compartment.intersection(left_compartment)
    return sum(map(item_priority, overlap))


while True:
    try:
        rucksack = input()
        total += process_rucksack(rucksack)
    except EOFError:
        break

print(total)
