#include "stdio.h"
#include "string.h"

#define MAX_HEIGHT 100
#define MAX_WIDTH 100

void tilt(
    const int width, const int height,
    char grid[][MAX_WIDTH + 1],
    const int x_offset, const int y_offset
) {
    const int isNS = (x_offset == 0);
    const int outer_end = isNS ? width : height;
    
    int inner_start, inner_end;
    if (isNS) {
        if (y_offset > 0) {
            inner_start = 0; inner_end = height;
        }
        else {
            inner_start = height - 1; inner_end = -1;
        }
    }
    else {
        if (x_offset > 0) {
            inner_start = 0; inner_end = width;
        }
        else {
            inner_start = width - 1; inner_end = -1;
        }
    }

    const int inner_offset = isNS ? y_offset : x_offset;

    for (int i = 0; i < outer_end; i++) {
        int position = inner_start;
        for (int j = inner_start; j != inner_end; j += inner_offset) {
            const int x = isNS ? i : j;
            const int y = isNS ? j : i;
            if (grid[y][x] == '#') {
                position = j + inner_offset;
            }

            if (grid[y][x] == 'O') {
                grid[y][x] = '.';
                if (isNS) {
                    grid[position][x] = 'O';
                }
                else {
                    grid[y][position] = 'O';
                }
                position += inner_offset;
            }
        }
    }
}

void cycle(const int width, const int height, char grid[][MAX_WIDTH + 1]) {
    tilt(width, height, grid, 0, 1);
    tilt(width, height, grid, 1, 0);
    tilt(width, height, grid, 0, -1);
    tilt(width, height, grid, -1, 0);
}

int grids_equal(const int height, char first[][MAX_WIDTH + 1], char second[][MAX_WIDTH + 1]) {
    for (int i = 0; i < height; i++) {
        if (strcmp(first[i], second[i]) != 0) return 0;
    }
    return 1;
}

int total_load(const int width, const int height, char grid[][MAX_WIDTH + 1]) {
    int total = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x] == 'O') {
                total += height - y;
            }
        }
    }
    return total;
}

int main(int argc, char **argv) {

    int num_lines = 0;
    char grid[MAX_HEIGHT][MAX_WIDTH + 1];
    while (scanf("%s", grid[num_lines]) == 1) {
        num_lines++;
    }

    const int width = strlen(grid[0]);

    char fast[MAX_HEIGHT][MAX_WIDTH + 1];
    memcpy(fast, grid, MAX_HEIGHT * (MAX_WIDTH + 1));

    int cycle_start = 0;
    do {
        cycle_start++;
        cycle(width, num_lines, grid);
        cycle(width, num_lines, fast); cycle(width, num_lines, fast);
    } while (!grids_equal(num_lines, grid, fast));

    printf("Cycle starts at %d\n", cycle_start);

    for (int i = 0; i < 1000000000 % cycle_start; i++) {
        cycle(width, num_lines, grid);
    }

    printf("Load on north support after 1000000000 cycles: %d\n", total_load(width, num_lines, grid));

    return 0;
}
