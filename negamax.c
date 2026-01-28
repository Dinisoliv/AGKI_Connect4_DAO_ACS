#include "negamax.h"
#include "evaluation.h"

int negamax(Metrics *metrics, const Position *P, int depth){

    metrics->nodeCount++;

    // Draw game
    if (Position_nbMoves(P) == WIDTH * HEIGHT)
        return 0;

    // Check if current player can win next move
    for (int x = 0; x < WIDTH; x++) {
        if (Position_canPlay(P, x) && Position_isWinningMove(P, x))
            return WIN_SCORE - Position_nbMoves(P);
    }

    //returns the heuristic result
    if (depth == 0)
        return evaluate_board(P);

    int bestScore = LOSS_SCORE;

    for (int x = 0; x < WIDTH; x++) {
        if (Position_canPlay(P, x)) {
            Position P2 = *P;
            Position_play(&P2, x);

            int score = -negamax(metrics, &P2, depth - 1);
            if (score > bestScore)
                bestScore = score;
        }
    }

    return bestScore;
}

int negamax_move(Metrics *metrics, const Position *P, int depth){
    int bestMove = -1;
    int bestScore = LOSS_SCORE;

    metrics->nodeCount = 0;

    for (int x = 0; x < WIDTH; x++) {
        if (Position_canPlay(P, x)) {
            Position P2 = *P;
            Position_play(&P2, x);

            int score = -negamax(metrics, &P2, depth - 1);
            if (score > bestScore) {
                bestScore = score;
                bestMove = x;
            }
        }
    }
    return bestMove;
}
