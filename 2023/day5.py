#!/usr/bin/env python3

seeds = list(input().split())[1:]
seeds = list(map(int, seeds))

input()


def process_block(inputs):
    last_block = "location" in input()
    output_map = []

    line = input()
    while line:
        output_map.append(list(map(int, line.split())))
        line = input()

    output = []
    for item in inputs:
        for (output_start, input_start, length) in output_map:
            if (input_start <= item) and (item < input_start + length):
                output.append(output_start + item - input_start)
                break
        else:
            output.append(item)

    return output, last_block


location, last_block = process_block(seeds)
while not last_block:
    location, last_block = process_block(location)

print(min(location))
