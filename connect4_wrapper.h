#ifndef CONNECT4_WRAPPER_H
#define CONNECT4_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct c4_game* c4_game_t;

/* lifecycle */
c4_game_t c4_new_game(void);
void c4_free_game(c4_game_t g);

/* mirror external move */
void c4_pascal_play(c4_game_t g, int col);

/* Pascal chooses AND plays */
int c4_pascal_best(c4_game_t g);

/* queries */
int c4_pascal_can_play(c4_game_t g, int col);
int c4_pascal_is_terminal(c4_game_t g);

#ifdef __cplusplus
}
#endif

#endif
