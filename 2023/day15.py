#!/usr/bin/env python3

from functools import reduce
from dataclasses import dataclass


def hash(s: str) -> int:
    return reduce(lambda acc, c: ((acc + ord(c)) * 17) % 256, list(s), 0)


@dataclass
class Lense:
    label: str
    focal_length: int


if __name__ == "__main__":
    steps = input().split(',')
    print(sum(map(hash, steps)))

    boxes: [[Lense]] = [[] for _ in range(256)]
    for step in steps:
        if '=' in step:
            label, focal_length_str = step.split('=')
            focal_length = int(focal_length_str)
            index = hash(label)
            for existing_lense in boxes[index]:
                if existing_lense.label == label:
                    existing_lense.focal_length = focal_length
                    break
            else:
                boxes[index].append(Lense(label, focal_length))
        else:
            label = step[:-1]
            index = hash(label)
            boxes[index] = list(
                filter(lambda lense: lense.label != label, boxes[index])
            )

    score = 0
    for box_number, lenses in enumerate(boxes):
        for slot, lense in enumerate(lenses):
            score += (box_number + 1) * (slot + 1) * lense.focal_length

    print(score)
