#!/usr/bin/env python3

from enum import Enum, auto
from typing import NamedTuple, Dict, List, Set, Tuple


class Direction(Enum):
    up = auto()
    down = auto()
    left = auto()
    right = auto()


class Cell(NamedTuple):
    x: int
    y: int
    direction: Direction


mirror_directions: Dict[str, Dict[Direction, List[Direction]]] = {
    '\\': {
        Direction.up: [Direction.left],
        Direction.down: [Direction.right],
        Direction.left: [Direction.up],
        Direction.right: [Direction.down]
    },
    '/': {
        Direction.up: [Direction.right],
        Direction.down: [Direction.left],
        Direction.left: [Direction.down],
        Direction.right: [Direction.up]
    },
    '-': {
        Direction.up: [Direction.left, Direction.right],
        Direction.down: [Direction.left, Direction.right],
        Direction.left: [Direction.left],
        Direction.right: [Direction.right]
    },
    '|': {
        Direction.up: [Direction.up],
        Direction.down: [Direction.down],
        Direction.left: [Direction.up, Direction.down],
        Direction.right: [Direction.up, Direction.down]
    },
    '.': {
        Direction.up: [Direction.up],
        Direction.down: [Direction.down],
        Direction.left: [Direction.left],
        Direction.right: [Direction.right]
    }
}

x_offsets: Dict[Direction, int] = {
    Direction.up: 0,
    Direction.down: 0,
    Direction.left: -1,
    Direction.right: 1
}


y_offsets: Dict[Direction, int] = {
    Direction.up: -1,
    Direction.down: 1,
    Direction.left: 0,
    Direction.right: 0
}


def energised_cells(grid: List[str]) -> int:
    cells_to_visit: List[Cell] = [
        Cell(0, 0, direction) for
        direction in mirror_directions[grid[0][0]][Direction.right]
    ]
    cells_visited: Set[Cell] = set()
    while len(cells_to_visit):
        current_cell = cells_to_visit.pop()

        if current_cell in cells_visited:
            continue
        cells_visited.add(current_cell)

        x: int = current_cell.x + x_offsets[current_cell.direction]
        y: int = current_cell.y + y_offsets[current_cell.direction]

        if y < 0 or y >= len(grid):
            continue
        if x < 0 or x >= len(grid[y]):
            continue

        cells_to_visit.extend(
            Cell(x, y, next_direction) for next_direction in
            mirror_directions[grid[y][x]][current_cell.direction]
        )

    positions_visited: Set[Tuple[int, int]] = set(
        (cell.x, cell.y) for cell in cells_visited
    )
    return len(positions_visited)


if __name__ == "__main__":
    grid: List[str] = []

    while True:
        try:
            grid.append(input())
        except EOFError:
            break

    print(energised_cells(grid))
