#include "stdio.h"
#include "string.h"

#define MAX_WIDTH 100

int main(int argc, char **argv) {

    int total_load = 0;
    int num_rocks = 0;
    int num_lines = 0;

    char line[MAX_WIDTH + 1];
    int positions[MAX_WIDTH];
    memset(positions, 0, MAX_WIDTH * sizeof(int));

    while (scanf("%s", line) == 1) {
        num_lines++;
        for (int i = 0; line[i]; i++) {
            if (line[i] == '#') {
                positions[i] = num_lines;
            }

            if (line[i] == 'O') {
                total_load += positions[i];
                positions[i]++;
                num_rocks++;
            }
        }
    }

    total_load = num_rocks * num_lines - total_load;
    printf("%d\n", total_load);

    return 0;
}
