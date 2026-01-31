#ifndef ALPHABETA_TT_H
#define ALPHABETA_TT_H

#include "GameCore.h"
#include "evaluation.h"

//inicializes the table and the tt_hits & tt_probes;
void alphabeta_tt_init(void);

//runs the algorithm and returns the bestmove
int  alphabeta_tt_move(Metrics *metrics, const Position *P, int depth);

//getters for the alphabeta transposition table hits and probes
unsigned long long alphabeta_tt_hits(void);
unsigned long long alphabeta_tt_probes(void);

#endif
