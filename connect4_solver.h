#ifndef CONNECT4_SOLVER_H
#define CONNECT4_SOLVER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// opaque handle
typedef void* c4_position_t;

// lifecycle
c4_position_t c4_create();
void c4_destroy(c4_position_t pos);

// gameplay
int c4_can_play(c4_position_t pos, int col);
void c4_play(c4_position_t pos, int col);

// solver
int c4_best_move(c4_position_t pos);

// optional evaluation
int c4_solve(c4_position_t pos);

#ifdef __cplusplus
}
#endif

#endif
