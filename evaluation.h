#ifndef EVALUATION_H
#define EVALUATION_H

#include "GameCore.h"

#define WIN_SCORE  INT_MAX
#define LOSS_SCORE INT_MIN

/*
 * Evaluates the board from the AI's perspective.
 * Positive values favor AI, negative values favor the opponent.
 */
int evaluate_board(const Position *position);

#endif
