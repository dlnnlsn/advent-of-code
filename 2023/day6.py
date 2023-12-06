#!/usr/bin/env python3

import math

times = input().split()
times = list(map(int, times[1:]))

distances = input().split()
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
