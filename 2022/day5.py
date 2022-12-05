#!/usr/bin/env python3

piles = []

line = input()
while not line.startswith("move"):
    if line.startswith(" "):
        break
    for i in range(1, len(line), 4):
        pile_no = i // 4
        if len(piles) <= pile_no:
            piles.append([])
        if line[i] != ' ':
            piles[pile_no].append(line[i])
    line = input()

_blank_line = input()
piles = [pile[::-1] for pile in piles]

while True:
    try:
        words = input().split()
        crates_to_move = int(words[1])
        pile_from = int(words[3]) - 1
        pile_to = int(words[5]) - 1
        if pile_from == pile_to:
            continue
        for _ in range(crates_to_move):
            item = piles[pile_from].pop()
            piles[pile_to].append(item)
    except EOFError:
        break

print("".join(pile[-1] for pile in piles))
