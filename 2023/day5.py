#!/usr/bin/env python3

def process_block(inputs):
    last_block = "location" in input()
    output_map = []

    line = input()
    while line:
        destination_start, source_start, length = map(int, line.split())
        output_map.append((
            source_start,
            source_start + length - 1,
            destination_start,
            destination_start + length - 1
        ))
        line = input()

    output_map.sort()
    output = []

    for (input_start, input_end) in inputs:
        for (
            source_start, source_end,
            destination_start, destination_end
        ) in output_map:
            if source_start > input_end:
                output.append((input_start, input_end))
                break
            if source_end < input_start:
                continue
            if input_start < source_start:
                output.append((input_start, source_start - 1))
                input_start = source_start
            if input_end <= source_end:
                output.append((
                    destination_start + input_start - source_start,
                    destination_start + input_end - source_start
                ))
                break
            output.append((
                destination_start + input_start - source_start,
                destination_end
            ))
            input_start = source_end + 1
        else:
            output.append((input_start, input_end))

    return output, last_block


seeds = input().split()[1:]
seeds = list(map(int, seeds))

seed_pairs = zip(seeds[::2], seeds[1::2])
seed_pairs = [(start, start + length - 1) for (start, length) in seed_pairs]
seed_pairs.sort()

input()

location, last_block = process_block(seed_pairs)
while not last_block:
    location, last_block = process_block(location)

print(min(location)[0])
