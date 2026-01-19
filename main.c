#include <stdio.h>

#include "Position.h"
#include "negamax.h"
#include "timeUtil.h"

int main(void){

    Solver solver;
    Solver_init(&solver);

    char line[256];
    int l = 1;

    while(fgets(line, sizeof(line), stdin)){
        line[strcspn(line, "\n")] = 0;

        Position P;
        Position_init(&P);

        if(Position_playSequence(&P, line) != strlen(line)) {
            fprintf(stderr, "Line %d: Invalid move %u \"%s\"\n", l, Position_nbMoves(&P), line);
        }else{
            //start Timer
            int score = Solver_solve(&solver, &P);
            //end Timer

            printf("%s %d %llu ", line, score, Solver_getNodeCount(&solver) /*, start-end times*/); //falta um %llu
        }

        printf("\n");
        l++;
    }
    
    return 0;
}