#ifndef NEGAMAX_H
#define NEGAMAX_H

#include "GameCore.h"

typedef struct {
    unsigned long long nodeCount;
} Solver;


void Solver_init(Solver *solver);//inicializes the solver structure

int negamax_move(Solver *solver, const Position *P, int depth); //runs the algorithm/solver

unsigned long long Solver_getNodeCount(const Solver *solver); // get function for nodeCount


#endif 