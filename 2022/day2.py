#!/usr/bin/env python3

outcomes = {
    'A': {'X': 3, 'Y': 1, 'Z': 2},
    'B': {'X': 1, 'Y': 2, 'Z': 3},
    'C': {'X': 2, 'Y': 3, 'Z': 1},
}

scores = {
    'X': 0,
    'Y': 3,
    'Z': 6,
}

score = 0

while True:
    try:
        opp, me = input().split()
        score += outcomes[opp][me] + scores[me]
    except EOFError:
        break

print(score)
