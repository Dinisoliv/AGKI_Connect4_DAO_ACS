#include "connect4_solver.h"

int main() {
    c4_position_t pos = c4_create();

    c4_play(pos, 3);
    c4_play(pos, 2);

    int move = c4_best_move(pos);
    printf("Perfect move: %d\n", move);

    c4_destroy(pos);
    return 0;
}
