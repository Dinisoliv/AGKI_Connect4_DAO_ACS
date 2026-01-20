#include <stdio.h>

#include "config.h"
#include "GameCore.h"
#include "negamax.h"

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
            double start = cpu_time();
            int score = Solver_solve(&solver, &P);
            double end = cpu_time();

            printf("%s %d %llu %d", line, score, Solver_getNodeCount(&solver), start-end);
        }

        printf("\n");
        l++;
    }
    
    return 0;
}

int main(void){
    Solver solver;
    Solver_init(&solver);

    while(true){

        Position P;
        Position_init(&P);

        if(ALG == "negamax"){

        }else if(ALG == "alpha-beta"){

        }else if(ALG == "other"){
            
        }else{
            fprintf(stderr, "Not a valid algorithm.");
            break;
        }
    }
}