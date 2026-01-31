#include <stdio.h>
#include "iterative.h"
#include "alphabeta_tt.h"

int iterative_deepening_move(Metrics *metrics, const Position *pos, int maxDepth) {
    int bestMove = -1;

    for (int depth = 1; depth <= maxDepth; depth++) {

        metrics->nodeCount = 0;

        int move = alphabeta_tt_move(metrics, pos, depth);

        if (move != -1) {
            bestMove = move;
        }

        printf(
            "[ID] depth=%d  bestMove=%d  nodes=%lld\n",
            depth,
            bestMove,
            metrics->nodeCount
        );
    }

    return bestMove;
}
