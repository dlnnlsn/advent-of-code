#!/usr/bin/env python3

comms = input()

counts = {}
distinct = 0

for i, c in enumerate(comms):
    if i >= 4:
        prev = comms[i - 4]
        if counts[prev] == 1:
            distinct -= 1
        counts[prev] -= 1
    if c in counts:
        if counts[c] == 0:
            distinct += 1
        counts[c] += 1
    else:
        distinct += 1
        counts[c] = 1
    if distinct == 4:
        print(i + 1)
        break
