function is_numeric(c: string | undefined) {
    if (c === undefined) return false;
    return (c >= '0') && (c <= '9');
}

function is_symbol(c: string | undefined) {
    if (c === undefined) return false;
    return !is_numeric(c) && (c !== '.');
}

function touches_symbol(x_start: number, x_end: number, y: number, engine: Array<string>) {
    for (let x = x_start - 1; x <= x_end; x++) {
        if (is_symbol(engine[y - 1]?.[x])) return true;
    }
    if (is_symbol(engine[y]?.[x_start - 1])) return true;
    if (is_symbol(engine[y]?.[x_end])) return true;
    for (let x = x_start - 1; x <= x_end; x++) {
        if (is_symbol(engine[y + 1]?.[x])) return true;
    }
    return false;
}

async function main() {
    let data = "";
    for await (const chunk of process.stdin) {
        data += chunk;
    }

    let total = 0;
    const engine = data.split('\n');
    for (let i = 0; i < engine.length; i++) {
        let start = 0;
        while ((start < engine[i].length) && !is_numeric(engine[i][start])) {
            start++;
        }
        let j = start;;
        while (j < engine[i].length) {
            while ((j < engine[i].length) && is_numeric(engine[i][j])) {
                j++;
            }
            const number = Number(engine[i].substring(start, j));
            if (touches_symbol(start, j, i, engine)) {
                total += number;
            } 
            while ((j < engine[i].length) && !is_numeric(engine[i][j])) {
                j++;
            }
            start = j;
        }
    }

    process.stdout.write(`${total}\n`);
}

main();
