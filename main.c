#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "GameCore.h"
#include "negamax.h"
#include "random.h"
#include "elapsed_time.h"
#include "helpers.h"

int main(void) {

    Position pos;
    Metrics metrics;
    
    Position_init(&pos);
    metrics_init(&metrics);

    double t1, t2;

    srand((unsigned int)time(NULL)); // Inicializes the rand function
    //metrics_reset();

    while (1) {
        int move;

        if(Position_nbMoves(&pos) %2 == 0){

            if (ALG == NEGAMAX){
                t1 = cpu_time();
                move =  negamax_move(&metrics, &pos, DEPTH);
                t2 = cpu_time();
                metrics.time += t2 - t1;
            }else if(ALG == ALPHABETA){
                t1 = cpu_time();
                move = alphabeta_move(&metrics, &pos, DEPTH);
                t2 = cpu_time();
                metrics.time += t2 - t1;
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
            int winnerPlayer = 1 + ((pos.moves - 1) % 2);
            printf("Player %d wins!\n", winnerPlayer);
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
    
    printf("Final board:\n");
    print_board(&pos);
    printf("Node count: %llu\n", metrics.nodeCount);
    printf("CPU Time:  %.6f seconds\n", metrics.time);

    write_result_to_csv("results.csv",
                        1 + ((pos.moves - 1) % 2),
                        metrics_getNodeCount(&metrics),
                        metrics_getTime(&metrics));

    return 0;
}
