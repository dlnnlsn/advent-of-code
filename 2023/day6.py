#!/usr/bin/env python3

import math

PART_TWO = True

times = input().split()
if PART_TWO:
    times = [int("".join(times[1:]))]
else:
    times = list(map(int, times[1:]))

distances = input().split()
if PART_TWO:
    distances = [int("".join(distances[1:]))]
else:
    distances = list(map(int, distances[1:]))

number_of_ways = 1

for (time, distance) in zip(times, distances):
    if time**2 < (4 * distance):
        number_of_ways = 0
        break
    discriminant = time**2 - 4 * distance
    ways = math.isqrt(discriminant)
    if ways**2 == discriminant:
        ways -= 2
    number_of_ways *= (ways + 1)

print(number_of_ways)
