#!/usr/bin/env python3

from functools import reduce


def hash(s: str) -> int:
    return reduce(lambda acc, c: ((acc + ord(c)) * 17) % 256, list(s), 0)


if __name__ == "__main__":
    steps = input().split(',')
    print(sum(map(hash, steps)))
