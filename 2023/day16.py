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


def energised_cells(grid: List[str], starting_cell: Cell) -> int:
    x, y, starting_direction = starting_cell
    cells_to_visit: List[Cell] = [
        Cell(x, y, direction) for
        direction in mirror_directions[grid[y][x]][starting_direction]
    ]
    cells_visited: Set[Cell] = set()
    while len(cells_to_visit):
        current_cell = cells_to_visit.pop()

        if current_cell in cells_visited:
            continue
        cells_visited.add(current_cell)

        x = current_cell.x + x_offsets[current_cell.direction]
        y = current_cell.y + y_offsets[current_cell.direction]

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

    print("Part 1: ", energised_cells(grid, Cell(0, 0, Direction.right)))

    # Not very efficient since a lot of work is duplicated,
    # but probably good enough:
    max_energised = -1
    for x in range(len(grid[0])):
        max_energised = max(
            max_energised,
            energised_cells(grid, Cell(x, 0, Direction.down)),
            energised_cells(grid, Cell(x, len(grid) - 1, Direction.up))
        )

    for y in range(len(grid)):
        max_energised = max(
            max_energised,
            energised_cells(grid, Cell(0, y, Direction.right)),
            energised_cells(grid, Cell(len(grid[0]) - 1, y, Direction.left))
        )
    print("Part 2: ", max_energised)
