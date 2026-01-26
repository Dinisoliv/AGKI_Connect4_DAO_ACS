#ifndef CONFIG_H
#define CONFIG_H


typedef enum {
    ALG_NEGAMAX,
    ALG_NEGAMAX_AB
    ALG_NEGAMAX_ID  //interactive deepenning
} Algorithm;

typedef enum {
    OPP_RANDOM,
    OPP_GREEDY,
    OPP_NEGAMAX
} OpponentType;

typedef struct {
    Algorithm alg;
    int depth;
    OpponentType p1;
    OpponentType p2;
} Config;

#endif