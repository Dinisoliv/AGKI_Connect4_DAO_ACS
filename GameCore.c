#include "GameCore.h"

void Position_init(Position *pos){
    for(int x = 0; x < WIDTH; x++){
        pos->height[x] = 0;
        for(int y = 0; y < HEIGHT; y++){
            pos->board[x][y] = 0;
        }
    }
    pos->moves = 0;
}

bool Position_canPlay(Position *pos, int col){
    return pos->height[col] < HEIGHT;
}

void Position_play(Position *pos, int col){
    int current_player = 1 + (pos->moves % 2);

    pos->board[col][pos->height[col]] = current_player;
    pos->height[col]++;
    pos->moves++;
}

unsigned int Position_playSequence(Position *pos, const char *seq){
    for(unsigned int i = 0; seq[i] != "\0"; i++){
        int col = seq[i]- '1';

        //checks for invalid moves;
        if(col < 0 || col >= WIDTH || !Position_canPlay(pos, col) ||
         Position_isWinningMove(pos, col)){
            return i;
        }

        Position_play(pos, col);
    }
    return 0; 
}

bool Position_isWinningMove(const Position *pos, int col){
    int current_player = 1 + (pos->moves % 2);
    int row = pos->height[col] - 1; 

    //Vertical check
    if(row >= 3 && pos->board[col][row] == current_player && pos->board[col][row -1] == current_player
         && pos->board[col][row-2] == current_player){
            return true;
    }

    //horizontal & diagonal check
    for (int dy = -1; dy <= 1; dy++) {
        int nb = 0;

        for (int dx = -1; dx <= 1; dx += 2) {
            int x = col + dx;
            int y = row + dx * dy;

            while (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT &&
                   pos->board[x][y] == current_player) {
                nb++;
                x += dx;
                y += dx * dy;
            }
        }

        if (nb >= 3) {
            return true;
        }
    }
    
    return false;
}


unsigned int Position_nbMoves(const Position *pos){
    return pos->moves;  
}