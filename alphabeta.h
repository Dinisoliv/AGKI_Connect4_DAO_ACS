#ifndef ALPHABETA_H
#define ALPHABETA_H

#include "GameCore.h"

typedef struct {
    unsigned long long nodeCount;
} Solver;


void alphabeta_init(Solver *solver); //inicializes the solver structure

int alphabeta_move(Solver *solver, const Position *P, int depth); //runs the algorithm/solver

unsigned long long alphabeta_getNodeCount(const Solver *solver); // get function for nodeCount


#endif 