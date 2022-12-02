#!/usr/bin/env python3

outcomes = {
    'A': {'X': 3, 'Y': 6, 'Z': 0},
    'B': {'X': 0, 'Y': 3, 'Z': 6},
    'C': {'X': 6, 'Y': 0, 'Z': 3},
}

scores = {
    'X': 1,
    'Y': 2,
    'Z': 3,
}

score = 0

while True:
    try:
        opp, me = input().split()
        score += outcomes[opp][me] + scores[me]
    except EOFError:
        break

print(score)
