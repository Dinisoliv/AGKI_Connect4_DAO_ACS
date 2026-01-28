#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "GameCore.h"
#include "negamax.h"
#include "random.h"

int main(void) {

    Position pos;
    Metrics metrics;
    
    Position_init(&pos);
    metrics_init(&metrics);

    srand((unsigned int)time(NULL)); // Inicializes the rand function
    //metrics_reset();

    while (1) {
        int move;

        if(Position_nbMoves(&pos) %2 == 0){

            if (ALG == NEGAMAX){
                move =  negamax_move(&metrics, &pos, DEPTH);
            }else if(ALG == ALPHABETA){
                move = alphabeta_move(&metrics, &pos, DEPTH);
            
            }else{
                //add others;
                printf("not a valid algorithm");
                break;
            }

        }else{
            if(OPP == RANDOM){
                move = random_move(&pos);
            }else{
                //add others
                printf("not a valid opponent");
                break;
            }
        }

        if (!Position_canPlay(&pos, move)) {
            fprintf(stderr, "Invalid move %d\n", move);
            break;
        }

        Position_play(&pos, move);

        if (Position_isWinningMove(&pos, move)) {
            printf("Player %d wins!\n", 1 + ((pos.moves - 1) % 2));
            break;
        }
        else if (Position_nbMoves(&pos) == WIDTH * HEIGHT) {
            printf("Draw!\n");
            break;    srand((unsigned int)time(NULL)); // Inicializes the rand function
        }
    }

    //Print final board / Save metrics in a file
    //Metrics m = metrics_get();
    //printf("Nodes expanded: %lld\n", m.nodes_expanded);
    //printf("Time: %.2f ms\n", m.time_ms);

    return 0;
}
