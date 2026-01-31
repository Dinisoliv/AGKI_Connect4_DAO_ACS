#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "GameCore.h"
#include "negamax.h"
#include "random.h"
#include "elapsed_time.h"
#include "helpers.h"
#include "alphabeta_tt.h"
#include "alphabeta.h"
#include "connect4_wrapper.h"

int main(void) {

    Position pos;
    Metrics metrics;
    c4_position_t pos_Op = c4_create();
    
    Position_init(&pos);
    metrics_init(&metrics);

    pos_Op = c4_create();

    double t1, t2;
    int winnerPlayer = 0;

    srand((unsigned int)time(NULL)); // Inicializes the rand function

    while (1) {
        int move;

        if(Position_nbMoves(&pos) %2 == 0){

            if (ALG == NEGAMAX){
                t1 = cpu_time();
                move =  negamax_move(&metrics, &pos, DEPTH);
                t2 = cpu_time();
            }else if(ALG == ALPHABETA){
                t1 = cpu_time();
                move = alphabeta_move(&metrics, &pos, DEPTH);
                t2 = cpu_time();
            }else if(ALG == ALPHABETA_TT){
                t1 = cpu_time();
                alphabeta_tt_init();
                move = alphabeta_tt_move(&metrics, &pos, DEPTH);
                t2 = cpu_time();
            }else{
                //add others;
                printf("not a valid algorithm");
                break;
            }

            metrics.time += (t2 - t1);
            printf("%d\n", move);

        }else{
            if(OPP == RANDOM){
                move = random_move(&pos);
            }else if (OPP == PERFECT) {   /* ← PascalPons */
                move = c4_best_move(solver_pos);
            }

            else{
                fprintf(stderr, "Invalid opponent\n");
                break;
            }
        }

        if (!Position_canPlay(&pos, move)) {
            fprintf(stderr, "Invalid move %d\n", move);
            break;
        }

        /* APPLY MOVE TO BOTH ENGINES */
        Position_play(&pos, move);
        c4_play(solver_pos, move);
        printf("%d\n", move);

        if (Position_isWinningMove(&pos, move)) {
            winnerPlayer = 1 + ((pos.moves - 1) % 2);
            printf("Player %d wins!\n", winnerPlayer);
            break;
        }
        else if (Position_nbMoves(&pos) == WIDTH * HEIGHT) {
            printf("Draw!\n");
            break;    srand((unsigned int)time(NULL)); // Inicializes the rand function
        }
    }

    //Print final board / Save n print metrics in a file
    
    printf("Final board:\n");
    print_board(&pos);
    printf("Node count: %llu\n", metrics.nodeCount);
    printf("CPU Time:  %.6f seconds\n", metrics.time);

    write_result_to_csv("results.csv",
                        winnerPlayer,
                        metrics.nodeCount,
                        metrics.time);

    c4_destroy(pos_Op);

    return 0;
}
