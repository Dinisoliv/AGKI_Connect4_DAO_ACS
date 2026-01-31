#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include "GameCore.h"


/**
 * Writes one result line to a CSV file.
 * If the file does not exist, it is created and a header is written.
 * If it exists, data is appended.
 */
void write_result_to_csv(const char *filename,
                         int winnerPlayer,
                         unsigned long long nodeCount,
                         double time, 
                         double hit_rate);

/* Print the board to stdout */
void print_board(const Position *pos);

#endif /* CSV_LOGGER_H */
