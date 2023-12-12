#!/usr/bin/env python3

from typing import Iterable, List
from functools import reduce

NUM_COPIES = 5


def solve_case(record: str, clues: Iterable[int]) -> int:
    record = '?'.join(record for _ in range(NUM_COPIES))
    clues = list(clues) * NUM_COPIES

    run_lengths = [0] * len(record)
    run_lengths[0] = 1 if record[0] != '.' else 0
    for (i, spring) in enumerate(record[1:]):
        run_lengths[i + 1] = run_lengths[i] + 1 if spring != '.' else 0

    assignments = [[0] * (len(clues) + 1) for _ in range(len(record) + 1)]
    assignments[0][0] = 1

    any_definitely_broken = False

    for (i, spring) in enumerate(record):
        any_definitely_broken = any_definitely_broken or spring == '#'
        assignments[i + 1][0] = 0 if any_definitely_broken else 1

        for (j, clue) in enumerate(clues):
            assignments[i + 1][j + 1] = 0
            if spring != '#':
                assignments[i + 1][j + 1] = assignments[i][j + 1]

            if run_lengths[i] < clue:
                continue

            if clue == (i + 1):
                assignments[i + 1][j + 1] += assignments[0][j]
                continue

            if record[i - clue] == '#':
                continue

            assignments[i + 1][j + 1] += assignments[i - clue][j]

    return assignments[-1][-1]


if __name__ == "__main__":
    total = 0
    while True:
        try:
            record, clues_str = input().split()
            clues = map(int, clues_str.split(","))
            total += solve_case(record, clues)
        except EOFError:
            break
    print(total)
