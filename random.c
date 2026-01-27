#include "random.h"
#include <stdlib.h>
#include <time.h>

int random_move(const Position *pos) {
    int valid_cols[WIDTH];
    int count = 0;

    // Collect all playable columns
    for (int x = 0; x < WIDTH; x++) {
        if (Position_canPlay((Position *)pos, x)) {
            valid_cols[count++] = x;
        }
    }

    // Safety check
    if (count == 0) {
        return -1;
    }

    // Pick one at random
    int r = rand() % count;
    return valid_cols[r];
}
