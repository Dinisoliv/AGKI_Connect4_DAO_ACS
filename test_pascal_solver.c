#include <assert.h>
#include <stdio.h>

#include "connect4_wrapper.h"

/*
 * Mid-game test position (safe, non-terminal)
 *
 * Moves:
 *   3 3 2 2 4 4 1 1
 *
 * Board is balanced, no immediate wins.
 */
static const int MIDGAME_MOVES[] = {3,3,2,2,4,4,1,1};

//make col 0 full
static const int FULL_COL0_MOVES[] = {0,0,0,0,0,0};

static const int MIDGAME_MOVES_2[] = {
    3, 2,
    3, 2,
    4, 1,
    4, 1
};


static const int MIDGAME_MOVES_3[] = {
    0, 6,
    1, 5,
    3, 3,
    2, 4
};

static const int MIDGAME_LEN = sizeof(MIDGAME_MOVES) / sizeof(int);
static const int MIDGAME_LEN_2 = sizeof(MIDGAME_MOVES_2) / sizeof(int);
static const int MIDGAME_LEN_3 = sizeof(MIDGAME_MOVES_3) / sizeof(int);

static const int FULL_COL0_LEN = sizeof(FULL_COL0_MOVES) / sizeof(int);

int main(void) {
    printf("Creating Pascal game...\n");
    c4_game_t g = c4_new_game();
    assert(g != NULL);

    printf("Playing mid-game moves...\n");
    for (int i = 0; i < FULL_COL0_LEN; ++i) {
        int col = FULL_COL0_MOVES[i];
        c4_pascal_play(g, col);
    }

    printf("Requesting Pascal best move...\n");
    int move = c4_pascal_best(g);

    printf("Pascal returned move: %d\n", move);

    /* ---- Assertions ---- */

    assert(move >= 0 && move < 7);        // valid column
    assert(c4_pascal_can_play(g, move)); // playable column
    assert(move != -1);                  // solver must choose

    printf("Move accepted.\n");

    /* Play returned move to ensure no crash */
    c4_pascal_play(g, move);

    printf("Freeing game...\n");
    c4_free_game(g);

    printf("✅ Pascal wrapper test PASSED\n");
    return 0;
}
