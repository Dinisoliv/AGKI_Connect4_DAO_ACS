#include "alphabeta.h"


int alphabeta(Metrics *metrics, const Position *P, int depth, int alpha, int beta){

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
    int bestScore = LOSS_SCORE;

    int alpha = LOSS_SCORE;
    int beta = WIN_SCORE;

    metrics->nodeCount = 0;

    for (int x = 0; x < WIDTH; x++){
        if (Position_canPlay(P, x)){
            Position P2 = *P;
            Position_play(&P2, x);

            int score = -alphabeta(metrics, &P2, depth - 1, -alpha, -beta);

            if (score > bestScore){
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