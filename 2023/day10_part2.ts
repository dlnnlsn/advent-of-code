type Direction = "N" | "S" | "E" | "W";
type Pipe = "-" | "|" | "J" | "7" | "L" | "F";
type GridSymbol = Pipe | "S" | ".";

type Point = {
    x: number;
    y: number;
};

const directions: Array<Direction> = ["N", "S", "E", "W"];
const pipes: Array<Pipe> = ["-", "|", "J", "7", "L", "F"];

const pipe_directions: Record<Pipe, Array<Direction>> = {
    "-": ["E", "W"],
    "|": ["N", "S"],
    J: ["N", "W"],
    "7": ["S", "W"],
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

const mirrored: Record<Pipe, Pipe> = {
    "-": "-",
    "|": "|",
    J: "F",
    "7": "L",
    L: "7",
    F: "J",
};

function find_cycle(
    grid: Array<Array<GridSymbol>>,
    start: Point,
    initial_direction: Direction,
): Array<Array<boolean>> | undefined {
    let { x, y } = start;
    let from_direction = initial_direction;
    let part_of_cycle: Array<Array<boolean>> = [];

    while (grid[y]?.[x] !== "S") {
        if (grid[y]?.[x] === undefined) {
            return undefined;
        }

        if (grid[y][x] === ".") {
            return undefined;
        }

        if (!pipe_directions[grid[y][x]].includes(from_direction)) {
            return undefined;
        }

        if (!(y in part_of_cycle)) {
            part_of_cycle[y] = [];
        }
        part_of_cycle[y][x] = true;

        from_direction =
            pipe_directions[grid[y][x]][0] === from_direction
                ? pipe_directions[grid[y][x]][1]
                : pipe_directions[grid[y][x]][0];

        x += x_offsets[from_direction];
        y += y_offsets[from_direction];
        from_direction = opposite_direction[from_direction];
    }

    if (!(y in part_of_cycle)) {
        part_of_cycle[y] = [];
    }
    part_of_cycle[y][x] = true;

    const S_directions = [opposite_direction[initial_direction], from_direction]
        .sort()
        .join();

    for (const pipe of pipes) {
        if (S_directions == pipe_directions[pipe].join()) {
            grid[y][x] = pipe;
            break;
        }
    }

    return part_of_cycle;
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

    let cycle: Array<Array<boolean>> | undefined = undefined;

    for (let y = 0; y < grid.length; y++) {
        for (let x = 0; x < grid[y].length; x++) {
            if (grid[y][x] !== "S") continue;

            for (const direction of directions) {
                cycle ||= find_cycle(
                    grid,
                    {
                        x: x + x_offsets[direction],
                        y: y + y_offsets[direction],
                    },
                    opposite_direction[direction],
                );
                if (cycle) break;
            }

            break;
        }
        if (cycle) break;
    }

    if (cycle === undefined) {
        // Something went wrong because we were promised that the
        // starting point is part of a unique cycle
        throw new Error("Starting point not part of any cycle");
    }

    let area_enclosed: number = 0;
    let last_corner: Pipe | undefined = undefined;

    for (let y = 0; y < grid.length; y++) {
        let inside_loop: boolean = false;
        if (!(y in cycle)) {
            cycle[y] = [];
        }
        for (let x = 0; x < grid[y].length; x++) {
            if (!cycle[y][x]) {
                if (inside_loop) {
                    area_enclosed++;
                }
                continue;
            }

            if (grid[y][x] === "-") {
                continue;
            }

            if (grid[y][x] === "|") {
                inside_loop = !inside_loop;
                continue;
            }

            if (["L", "F"].includes(grid[y][x])) {
                last_corner = grid[y][x] as Pipe;
                continue;
            }

            if (grid[y][x] === mirrored[last_corner!]) {
                inside_loop = !inside_loop;
            }
        }
    }

    process.stdout.write(`${area_enclosed}\n`);
}

main();
