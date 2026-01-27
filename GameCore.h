#ifndef GAMECORE_H
#define GAMECORE_H

#include <stdbool.h>

#define WIDTH 7
#define HEIGHT 6

typedef struct {
  int board[WIDTH][HEIGHT];
  int height[WIDTH];
  unsigned int moves;
} Position;

//inicializes the position
void Position_init(Position *pos);

//checks if a collum is playable
bool Position_canPlay(Position *pos, int col);

/* Play a column (assumes playable & non-winning) */
void Position_play(Position *pos, int col);

/* Play a sequence of moves ("1234567") */
unsigned int Position_playSequence(Position *pos, const char *seq);

/* Check if playing a column is a winning move */
bool Position_isWinningMove(const Position *pos, int col);

/* Number of moves played */
unsigned int Position_nbMoves(const Position *pos);

/* Print the board to stdout */
void print_board(const Position *pos);

#endif /* POSITION_H */
