#ifndef CONNECT4_WRAPPER_H
#define CONNECT4_WRAPPER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* c4_position_t;

/* lifecycle */
c4_position_t c4_create(void);
void c4_destroy(c4_position_t pos);

/* gameplay */
int  c4_can_play(c4_position_t pos, int col);
void c4_play(c4_position_t pos, int col);

/* solver */
int c4_best_move(c4_position_t pos);
int c4_solve(c4_position_t pos);

#ifdef __cplusplus
}
#endif

#endif /* CONNECT4_WRAPPER_H */
