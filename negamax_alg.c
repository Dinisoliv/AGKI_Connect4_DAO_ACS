#include "negamax.h"

int negamax(Solver *solver, const Position *P){

    solver->nodeCount++;

    /* Draw game */
    if (Position_nbMoves(P) == WIDTH * HEIGHT)
        return 0;

    /* Check if current player can win next move */
    for (int x = 0; x < WIDTH; x++) {
        if (Position_canPlay(P, x) && Position_isWinningMove(P, x)) {
            return (WIDTH * HEIGHT + 1 - Position_nbMoves(P)) / 2;
        }
    }

    int bestScore = -WIDTH * HEIGHT;

    /* Try all possible moves */
    for (int x = 0; x < WIDTH; x++) {
        if (Position_canPlay(P, x)) {
            Position P2 = *P;          /* STRUCT COPY (replaces copy constructor) */
            Position_play(&P2, x);     /* opponent’s turn now */

            int score = -negamax(solver, &P2);
            if (score > bestScore)
                bestScore = score;
        }
    }

    return bestScore;
}


int Solver_solve(Solver *solver, const Position *P){
    solver->nodeCount = 0;
    return Solver_negamax(solver, P);
}

unsigned long long Solver_getNodeCount(const Solver *solver){
    return solver->nodeCount;
}

