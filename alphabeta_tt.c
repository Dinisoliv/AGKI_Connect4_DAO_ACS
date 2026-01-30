#include "alphabeta_tt.h"
#include "evaluation.h"
#include <stdint.h>
#include <string.h>

//Transposition Table

#define TT_SIZE (1 << 20)

typedef enum {
    TT_EMPTY,
    TT_EXACT,
    TT_LOWER,
    TT_UPPER
} TTFlag;

typedef struct {
    uint64_t key;
    int depth;
    int value;
    TTFlag flag;
} TTEntry;

static TTEntry table[TT_SIZE];

static inline unsigned tt_index(uint64_t key) {
    return key & (TT_SIZE - 1);
}

static uint64_t position_hash(const Position *P) {
    uint64_t h = 1469598103934665603ULL;
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < P->height[x]; y++) {
            h ^= (uint64_t)(P->board[x][y] + 7 * x + 13 * y);
            h *= 1099511628211ULL;
        }
    }
    return h ^ P->moves;
}

void alphabeta_tt_init(void) {
    memset(table, 0, sizeof(table));
}

static int tt_probe(uint64_t key, int depth, int alpha, int beta, int *value) {
    TTEntry *e = &table[tt_index(key)];

    if (e->key != key || e->depth < depth)
        return 0;

    if (e->flag == TT_EXACT) {
        *value = e->value;
        return 1;
    }
    if (e->flag == TT_LOWER && e->value >= beta) {
        *value = e->value;
        return 1;
    }
    if (e->flag == TT_UPPER && e->value <= alpha) {
        *value = e->value;
        return 1;
    }
    return 0;
}

static void tt_store(uint64_t key, int depth, int value, TTFlag flag) {
    TTEntry *e = &table[tt_index(key)];
    e->key = key;
    e->depth = depth;
    e->value = value;
    e->flag = flag;
}

//_____________________________________
//alphabeta_tt

static int alphabeta_tt(Metrics *metrics, const Position *P, int depth, int alpha, int beta) {
    
    metrics->nodeCount++;

    uint64_t key = position_hash(P);
    int ttValue;

    if (tt_probe(key, depth, alpha, beta, &ttValue))
        return ttValue;

    /* Draw */
    if (Position_nbMoves(P) == WIDTH * HEIGHT)
        return 0;

    /* Immediate win */
    for (int x = 0; x < WIDTH; x++) {
        if (Position_canPlay(P, x) && Position_isWinningMove(P, x)) {
            int win = WIN_SCORE - Position_nbMoves(P);
            tt_store(key, depth, win, TT_EXACT);
            return win;
        }
    }

    if (depth == 0)
        return evaluate_board(P);

    int bestScore = LOSS_SCORE;
    int alpha0 = alpha;

    for (int x = 0; x < WIDTH; x++) {
        if (Position_canPlay(P, x)) {
            Position P2 = *P;
            Position_play(&P2, x);

            int score = -alphabeta_tt(
                metrics, &P2, depth - 1,
                -beta, -alpha
            );

            if (score > bestScore)
                bestScore = score;

            if (bestScore > alpha)
                alpha = bestScore;

            if (alpha >= beta)
                break;
        }
    }

    TTFlag flag = (bestScore <= alpha0) ? TT_UPPER :(bestScore >= beta)   ? TT_LOWER : TT_EXACT;
    tt_store(key, depth, bestScore, flag);
    return bestScore;
}


int alphabeta_tt_move(Metrics *metrics, const Position *P, int depth) {
    int bestMove = -1;
    int bestScore = LOSS_SCORE;

    int alpha = LOSS_SCORE;
    int beta  = WIN_SCORE;

    metrics->nodeCount = 0;

    for (int x = 0; x < WIDTH; x++) {
        if (Position_canPlay(P, x)) {
            Position P2 = *P;
            Position_play(&P2, x);

            int score = -alphabeta_tt(
                metrics, &P2, depth - 1,
                -beta, -alpha
            );

            if (score > bestScore) {
                bestScore = score;
                bestMove = x;
            }

            if (bestScore > alpha)
                alpha = bestScore;
        }
    }
    return bestMove;
}
