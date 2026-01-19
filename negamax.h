#ifndef NEGAMAX_H
#define NEGAMAX_H

#include "position.h"

typedef struct {
    unsigned long long nodeCount;
} Solver;


void Solver_init(Solver *solver);//inicializes the solver structure

int  Solver_solve(Solver *solver, const Position *P); //runs the algorithm/solver

unsigned long long Solver_getNodeCount(const Solver *solver); // get function for nodeCount


#endif 