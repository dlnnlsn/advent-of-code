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

type DFSStackObject = {
    location: Point;
    from_direction: Direction;
    steps: number;
};

function dfs(
    grid: Array<Array<GridSymbol>>,
    start: Point,
    initial_direction: Direction,
): number | undefined {
    // Ordinarily we should keep track of the nodes already visited to
    // detect if we have entered a loop, but we can only enter a loop
    // by returning to the starting point, which we already test for

    const to_visit: Array<DFSStackObject> = [
        {
            location: start,
            from_direction: initial_direction,
            steps: 1,
        },
    ];

    while (to_visit.length > 0) {
        const {
            location: { x, y },
            from_direction: direction,
            steps,
        } = to_visit.pop()!;

        if (grid[y][x] === undefined) {
            continue;
        }

        if (grid[y][x] === ".") {
            continue;
        }

        if (grid[y][x] === "S") {
            return steps;
        }

        if (!pipe_directions[grid[y][x]].includes(direction)) {
            continue;
        }

        for (const pipe_direction of pipe_directions[grid[y][x]]) {
            if (pipe_direction == direction) continue;
            to_visit.push({
                location: {
                    x: x + x_offsets[pipe_direction],
                    y: y + y_offsets[pipe_direction],
                },
                from_direction: opposite_direction[pipe_direction],
                steps: steps + 1,
            });
        }
    }

    return undefined;
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

            let cycle_length: number | undefined = undefined;

            for (const direction of directions) {
                cycle_length ||= dfs(
                    grid,
                    {
                        x: x + x_offsets[direction],
                        y: y + y_offsets[direction],
                    },
                    opposite_direction[direction],
                );
            }

            if (cycle_length === undefined) {
                // Something went wrong because we were promised that the
                // starting point is part of a unique cycle
                throw new Error("Starting point not part of any cycle");
            }

            process.stdout.write(`${Math.floor(cycle_length / 2)}\n`);
            return;
        }
    }
}

main();
