type Point = {
    x: number;
    y: number;
};

function is_numeric(c: string | undefined) {
    if (c === undefined) return false;
    return c >= "0" && c <= "9";
}

function* touching_stars(
    x_start: number,
    x_end: number,
    y: number,
    engine: Array<string>,
): Array<Point> {
    for (let x = x_start - 1; x <= x_end; x++) {
        if (engine[y - 1]?.[x] === "*") {
            yield { x, y: y - 1 };
        }
    }
    if (engine[y][x_start - 1] === '*') {
        yield { y, x: x_start - 1 };
    }
    if (engine[y][x_end] === "*") {
        yield { y, x: x_end };
    }
    for (let x = x_start - 1; x <= x_end; x++) {
        if (engine[y + 1]?.[x] === "*") {
            yield { x, y: y + 1 };
        }
    }
}

type StarMap = Map<number, Map<number, Array<number>>>;

function insert_point({ x, y }: Point, value: number, stars: StarMap) {
    if (!stars.has(x)) {
        stars.set(x, new Map());
    }
    if (!stars.get(x).has(y)) {
        stars.get(x).set(y, []);
    }
    stars.get(x).get(y).push(value);
}

async function main() {
    let data = "";
    for await (const chunk of process.stdin) {
        data += chunk;
    }

    const stars: StarMap = new Map();

    const engine = data.split("\n");
    for (let i = 0; i < engine.length; i++) {
        let start = 0;
        while (start < engine[i].length && !is_numeric(engine[i][start])) {
            start++;
        }
        let j = start;
        while (j < engine[i].length) {
            while (j < engine[i].length && is_numeric(engine[i][j])) {
                j++;
            }
            const number = Number(engine[i].substring(start, j));
            for (const star_location of touching_stars(start, j, i, engine)) {
                insert_point(star_location, number, stars);
            }
            while (j < engine[i].length && !is_numeric(engine[i][j])) {
                j++;
            }
            start = j;
        }
    }

    let total = 0;

    for (const column of stars.values()) {
        for (const touching_numbers of column.values()) {
            if (touching_numbers.length === 2) {
                total += touching_numbers[0] * touching_numbers[1];
            }
        }
    }

    process.stdout.write(`${total}\n`);
}

main();
