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

char* filename2[] = {"results_AlphaBeta_3.csv",  "results_AlphaBeta_5.csv", "results_AlphaBeta_7.csv", "results_AlphaBeta_9.csv"};
char* filename4[] = {"results_Iterative_3.csv",  "results_Iterative_5.csv", "results_Iterative_7.csv", "results_Iterative_9.csv"};
char* filename3[] = {"results_AlphaBeta_TT_3.csv",  "results_AlphaBeta_TT_5.csv", "results_AlphaBeta_TT_7.csv", "results_AlphaBeta_TT_9.csv"};
char* filename1[] = {"results_Negamax_3.csv",  "results_Negamax_5.csv", "results_Negamax_7.csv", "results_Negamax_9.csv"};

int main(void) {

    int depth = 3;
    while (depth <= 9)
    {
        
    
    int i = 0;
    while (i < 50) // Number of games to play
    {

    /* ---------- YOUR ENGINE STATE ---------- */
    Position pos;
    Metrics metrics;

    /* ---------- PASCAL SOLVER STATE ---------- */
    //c4_game_t pascal;

    Position_init(&pos);
    metrics_init(&metrics);

    //pascal = c4_new_game();

    double t1, t2;
    int winnerPlayer = 0;

    srand((unsigned int)time(NULL));

    
        while (1) {
            int move;

            /* ---------- YOUR ENGINE TURN ---------- */
            if (Position_nbMoves(&pos) % 2 == 0) {

                t1 = cpu_time();

                if (ALG == NEGAMAX) {
                    move = negamax_move(&metrics, &pos, depth);
                } else if (ALG == ALPHABETA) {
                    move = alphabeta_move(&metrics, &pos, depth);
                } else if (ALG == ALPHABETA_TT) {
                    alphabeta_tt_init();
                    move = alphabeta_tt_move(&metrics, &pos, depth);
                } else if (ALG == ITERATIVE) {
                    alphabeta_tt_init();
                    move = iterative_deepening_move(&metrics, &pos, depth);
                } else {
                    fprintf(stderr, "Invalid algorithm\n");
                    break;
                }

                t2 = cpu_time();
                metrics.time += (t2 - t1);

                /* apply move to BOTH states */
                if (!Position_canPlay(&pos, move)) {
                    fprintf(stderr, "Invalid move %d\n", move);
                    break;
                }

                Position_play(&pos, move);
                //c4_pascal_play(pascal, move);

            }

            /* ---------- OPPONENT TURN ---------- */
            else {

                if (OPP == RANDOM) {
                    move = random_move(&pos);

                    if (!Position_canPlay(&pos, move)) {
                        fprintf(stderr, "Invalid move %d\n", move);
                        break;
                    }

                    Position_play(&pos, move);
                    //c4_pascal_play(pascal, move);

                } else if (OPP == PERFECT) {
                    /* Pascal solver chooses AND plays internally */
                    //move = c4_pascal_best(pascal);

                    /* mirror move into your engine */
                    if (!Position_canPlay(&pos, move)) {
                        fprintf(stderr, "Pascal played invalid move %d\n", move);
                        break;
                    }
                    
                    Position_play(&pos, move);

                // play based only on heuristic of next play
                } else if (OPP == MID) {
                    int best_score = -1000000;
                    int score;
                    for (int i = 0; i < 7; i++)
                    {
                        if (Position_canPlay(&pos, i)){
                            Position P2 = *(&pos);
                            Position_play(&P2, i);
                            score = evaluate_board(&P2);
                            if (score > best_score) {
                                best_score = score;
                                move = i;
                            }
                        }
                    }
                    if (!Position_canPlay(&pos, move)) {
                        fprintf(stderr, "Invalid move %d\n", move);
                        break;
                    }

                    Position_play(&pos, move);

                } else {
                    fprintf(stderr, "Invalid opponent\n");
                    break;
                }
            }

            printf("%d\n", move);

            /* ---------- TERMINAL CHECK (YOUR ENGINE) ---------- */
            if (Position_checkWin(&pos, move)) {
                winnerPlayer = 1 + ((pos.moves - 1) % 2);
                printf("Player %d wins!\n", winnerPlayer);
                break;
            } else if (Position_nbMoves(&pos) == WIDTH * HEIGHT) {
                printf("Draw!\n");
                break;
            }
        }

        /* ---------- RESULTS ---------- */

        printf("Final board:\n");
        print_board(&pos);

        printf("Node count: %llu\n", metrics.nodeCount);
        printf("CPU Time:  %.6f seconds\n", metrics.time);
        printf("TT probes: %llu\n", alphabeta_tt_probes());
        printf("TT hits: %llu\n", alphabeta_tt_hits());

        double hit_rate = 0.0;
        if (alphabeta_tt_probes() > 0) {
            hit_rate = 100.0 * alphabeta_tt_hits() / alphabeta_tt_probes();
            printf("TT hit rate: %.2f%%\n", hit_rate);
        }

        write_result_to_csv(filename4[depth/2-1],
                            winnerPlayer,
                            metrics.nodeCount,
                            metrics.time,
                            hit_rate);

        //c4_free_game(pascal);

        i++;

    }

    depth += 2;
    }
    return 0;
}
