#include "alphabeta.h"


int alphabeta(Metrics *metrics, const Position *P, int depth, int alpha, int beta){

    metrics->nodeCount++;

    //returns the heuristic result
    if(depth == 0){
        return heuristic(P);
    }
    // Draw game
    if (Position_nbMoves(P) == WIDTH * HEIGHT){
        return 0;
    }

    // Check if current player can win next move
    for (int x = 0; x < WIDTH; x++) {
        if (Position_canPlay(P, x) && Position_isWinningMove(P, x)) {
            return (WIDTH * HEIGHT + 1 - Position_nbMoves(P)) / 2;
        }
    }

    int bestScore = -WIDTH * HEIGHT;

    // Try all possible moves 
    for (int x = 0; x < WIDTH; x++) {   
        if (Position_canPlay(P, x)) {
            Position P2 = *P;          // STRUCT COPY (replaces copy constructor) 
            Position_play(&P2, x);     // opponent’s turn now 

            int score = -alphabeta(metrics, &P2, depth-1, -alpha, -beta);
            if (score > bestScore){
                bestScore = score;
            }
            if (bestScore > alpha){
                alpha = bestScore;
            }
            //pruning
            if (alpha >= beta){
                break;
            }

        }
    }

    return bestScore;
}


int alphabeta_move(Metrics *metrics, const Position *P, int depth){
    int bestMove = -1;
    int bestScore = -WIDTH * HEIGHT;

    int alpha = -WIDTH * HEIGHT;
    int beta = WIDTH * HEIGHT;

    metrics->nodeCount = 0;

    for (int x = 0; x < WIDTH; x++) {
        if (Position_canPlay(P, x)) {
            Position P2 = *P;
            Position_play(&P2, x);

            int score = -alphabeta(metrics, &P2, depth - 1, -alpha, -beta);

            if (score > bestScore) {
                bestScore = score;
                bestMove = x;
            }

            if (bestScore > alpha){
                alpha = bestScore;
            }
        }
    }
    return bestMove;
}