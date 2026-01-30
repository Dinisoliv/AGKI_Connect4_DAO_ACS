#ifndef ALPHABETA_TT_H
#define ALPHABETA_TT_H

#include "GameCore.h"
#include "evaluation.h"

void alphabeta_tt_init(void);
int  alphabeta_tt_move(Metrics *metrics, const Position *P, int depth);

#endif
