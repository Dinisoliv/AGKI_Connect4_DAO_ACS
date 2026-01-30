#include "helpers.h"
#include <stdlib.h>

void write_result_to_csv(const char *filename,
                         int winnerPlayer,
                         unsigned long long nodeCount,
                         double time)
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
        fprintf(file, "winnerPlayer,nodeCount,time\n");
    }

    fprintf(file, "%d,%llu,%.6f\n",
            winnerPlayer,
            nodeCount,
            time);

    fclose(file);
}
