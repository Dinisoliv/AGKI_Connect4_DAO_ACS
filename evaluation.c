#include "evaluation.h"

#define TWO_IN_ROW    10
#define THREE_IN_ROW  100

static int score_window(int p_count, int o_count);
static int evaluate_center(const Position *pos);
static int evaluate_windows(const Position *pos);

/* Public evaluation function */
int evaluate_position(const Position *pos)
{
    int score = 0;

    score += evaluate_center(pos);
    score += evaluate_windows(pos);

    return score;
}

// Evaluate center control
static int evaluate_center(const Position *pos)
{
    int score = 0;

    /* Progressive column weights (edges → center) */
    static const int col_weights[WIDTH] = {3, 4, 5, 7, 5, 4, 3};

    int phase = pos->moves;   // number of moves played

    int center_multiplier;
    if (phase < 8)
        center_multiplier = 3;   // opening
    else if (phase < 20)
        center_multiplier = 2;   // midgame
    else
        center_multiplier = 1;   // endgame

    for (int col = 0; col < WIDTH; col++) {
        for (int row = 0; row < pos->height[col]; row++) {
            if (pos->board[col][row] == PLAYER)
                score += center_multiplier * col_weights[col];
            else if (pos->board[col][row] == OPPONENT)
                score -= center_multiplier * col_weights[col];
        }
    }

    return score;
}


// Score a window of 4 cells
static int score_window(int player_count, int opp_count)
{
    if (player_count == 3 && opp_count == 0) return THREE_IN_ROW;
    if (player_count == 2 && opp_count == 0) return TWO_IN_ROW;
    if (opp_count == 3 && player_count == 0) return -THREE_IN_ROW;
    if (opp_count == 2 && player_count == 0) return -TWO_IN_ROW;
    return 0;
}

// Evaluate all possible windows of 4 in the board
static int evaluate_windows(const Position *pos)
{
    int score = 0;

    /* Horizontal (left-to-right) */
    for (int col = 0; col < WIDTH - 3; col++) {
        for (int row = 0; row < HEIGHT; row++) {
            int p = 0, o = 0;

            for (int i = 0; i < 4; i++) {
                if (row >= pos->height[col + i]) goto next_h;

                int cell = pos->board[col + i][row];
                if (cell == PLAYER) p++;
                else if (cell == OPPONENT) o++;
            }

            score += score_window(p, o);
next_h:;
        }
    }
<

    /* Vertical */
    for (int col = 0; col < WIDTH; col++) {
        for (int row = 0; row < pos->height[col] - 3; row++) {
            int p = 0, o = 0;

            for (int i = 0; i < 4; i++) {
                int cell = pos->board[col][row + i];
                if (cell == PLAYER) p++;
                else if (cell == OPPONENT) o++;
            }

            score += score_window(p, o);
        }
    }


    /* Diagonal (bottom-left to top-right) */
    for (int col = 0; col < WIDTH - 3; col++) {
        for (int row = 0; row < HEIGHT - 3; row++) {
            int p = 0, o = 0;

            for (int i = 0; i < 4; i++) {
                if (row + i >= pos->height[col + i]) goto next_d1;

                int cell = pos->board[col + i][row + i];
                if (cell == PLAYER) p++;
                else if (cell == OPPONENT) o++;
            }

            score += score_window(p, o);
next_d1:;
        }
    }


    /* Diagonal (top-left to bottom-right) */
    for (int col = 0; col < WIDTH - 3; col++) {
        for (int row = 3; row < HEIGHT; row++) {
            int p = 0, o = 0;

            for (int i = 0; i < 4; i++) {
                if (row - i >= pos->height[col + i]) goto next_d2;

                int cell = pos->board[col + i][row - i];
                if (cell == PLAYER) p++;
                else if (cell == OPPONENT) o++;
            }

            score += score_window(p, o);
next_d2:;
        }
    }

    return score;
}
