#include "stdio.h"
#include "string.h"

#define MAX_RECORD_LENGTH 20
#define MAX_NUMBER_OF_CLUES 20

int main(int argc, char **arg) {

    char record[MAX_RECORD_LENGTH + 1];
    int record_length;

    int run_lengths[MAX_RECORD_LENGTH];

    int clues[MAX_NUMBER_OF_CLUES];
    int num_clues;

    long long int
    assignments[MAX_RECORD_LENGTH + 1][MAX_NUMBER_OF_CLUES + 1];

    int num_definitely_broken[MAX_RECORD_LENGTH];

    long long int total = 0;

    while (scanf("%s", record) == 1) {
        record_length = strlen(record);

        num_clues = 0; 
        int clue;

        while (scanf("%d,", &clue) == 1) {
            clues[num_clues++] = clue;
        }

        if (scanf("%d", &clue) == 1) {
            clues[num_clues++] = clue;
        }

        run_lengths[0] = record[0] != '.';
        num_definitely_broken[0] = record[0] == '#';
        for (int i = 1; i < record_length; i++) {
            num_definitely_broken[i] =
                num_definitely_broken[i - 1] + (record[i] == '#');

            if (record[i] == '.') {
                run_lengths[i] = 0; continue;
            }

            run_lengths[i] = run_lengths[i - 1] + 1;
        }

        memset(assignments, 0, sizeof(long long int) * (num_clues + 1));
        assignments[0][0] = 1;

        for (int i = 1; i <= record_length; i++) {
            assignments[i][0] = num_definitely_broken[i - 1] == 0;
            
            for (int j = 1; j <= num_clues; j++) {
                assignments[i][j] = 0;
                if (record[i - 1] != '#') {
                    assignments[i][j] = assignments[i - 1][j];
                }

                if (run_lengths[i - 1] < clues[j - 1]) {
                    continue;
                }

                if (clues[j - 1] == i) {
                    assignments[i][j] += assignments[0][j - 1];
                    continue;
                }

                if (record[i - clues[j - 1] - 1] == '#') {
                    continue;
                }

                assignments[i][j] += assignments[i - clues[j - 1] - 1][j - 1];
            }
        }

        total += assignments[record_length][num_clues];
    }

    printf("Total:\t%lld\n", total);

    return 0;
}
