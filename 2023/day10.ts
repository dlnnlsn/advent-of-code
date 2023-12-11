type Direction = "N" | "S" | "E" | "W";
type Pipe = "-" | "|" | "J" | "7" | "L" | "F";
type GridSymbol = Pipe | "S" | ".";

type Point = {
    x: number;
    y: number;
};

const directions: Array<Direction> = ["N", "S", "E", "W"];

const pipe_directions: Record<Pipe, Array<Direction>> = {
    "-": ["E", "W"],
    "|": ["N", "S"],
    J: ["W", "N"],
    "7": ["W", "S"],
    L: ["E", "N"],
    F: ["E", "S"],
};

const x_offsets: Record<Direction, number> = {
    N: 0,
    S: 0,
    E: 1,
    W: -1,
};

const y_offsets: Record<Direction, number> = {
    N: -1,
    S: 1,
    E: 0,
    W: 0,
};

const opposite_direction: Record<Direction, Direction> = {
    N: "S",
    S: "N",
    E: "W",
    W: "E",
};

function cycle_length(
    grid: Array<Array<GridSymbol>>,
    start: Point,
    initial_direction: Direction,
): number | undefined {
    let { x, y } = start;
    let from_direction = initial_direction;
    let steps = 1;

    while (grid[y][x] !== "S") {
        if (grid[y][x] === undefined) {
            return undefined;
        }

        if (grid[y][x] === ".") {
            return undefined;
        }

        if (!pipe_directions[grid[y][x]].includes(from_direction)) {
            return undefined;
        }

        from_direction =
            pipe_directions[grid[y][x]][0] === from_direction
                ? pipe_directions[grid[y][x]][1]
                : pipe_directions[grid[y][x]][0];

        x += x_offsets[from_direction];
        y += y_offsets[from_direction];
        from_direction = opposite_direction[from_direction];
        steps++;
    }

    return steps;
}

async function main() {
    let data = "";
    for await (const chunk of process.stdin) {
        data += chunk;
    }

    const grid = data
        .split("\n")
        .filter((line) => line)
        .map((line) => Array.from(line)) as Array<Array<GridSymbol>>;

    for (let y = 0; y < grid.length; y++) {
        for (let x = 0; x < grid[y].length; x++) {
            if (grid[y][x] !== "S") continue;

            let length: number | undefined = undefined;

            for (const direction of directions) {
                length ||= cycle_length(
                    grid,
                    {
                        x: x + x_offsets[direction],
                        y: y + y_offsets[direction],
                    },
                    opposite_direction[direction],
                );
            }

            if (length === undefined) {
                // Something went wrong because we were promised that the
                // starting point is part of a unique cycle
                throw new Error("Starting point not part of any cycle");
            }

            process.stdout.write(`${Math.floor(length / 2)}\n`);
            return;
        }
    }
}

main();
