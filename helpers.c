#include "helpers.h"
#include <stdlib.h>

void write_result_to_csv(const char *filename,
                         int winnerPlayer,
                         unsigned long long nodeCount,
                         double time,
                         double hit_rate)
{
    FILE *file = fopen(filename, "a+");
    if (!file) {
        perror("Failed to open CSV file");
        return;
    }

    // Check if file is empty
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);

    if (file_size == 0) {
        fprintf(file, "winnerPlayer,nodeCount,time,hit_rate\n");
    }

    fprintf(file, "%d,%llu,%.6f,%.2f\n",
            winnerPlayer,
            nodeCount,
            time,
            hit_rate
        );

    fclose(file);
}

void print_board(const Position *pos)
{
    for (int row = HEIGHT - 1; row >= 0; row--) {
        printf("| ");
        for (int col = 0; col < WIDTH; col++) {

            if (row < pos->height[col]) {
                if (pos->board[col][row] == 1)
                    printf("X ");
                else if (pos->board[col][row] == 2)
                    printf("O ");
                else
                    printf(". ");  // safety fallback
            } else {
                printf(". ");
            }
        }
        printf("|\n");
    }

    /* Column indices */
    printf("  ");
    for (int col = 0; col < WIDTH; col++)
        printf("%d ", col);
    printf("\n");
}
