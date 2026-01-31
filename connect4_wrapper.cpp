#include "connect4_wrapper.h"

#include <cassert>
#include <vector>

#include "Position.hpp"
#include "Solver.hpp"

using GameSolver::Connect4::Position;
using GameSolver::Connect4::Solver;

/*
 * Internal Pascal-owned game state.
 * This is opaque to C callers.
 */
struct c4_game {
    Position pos;
    Solver   solver;

    c4_game() : pos(), solver() {}
};

extern "C" {

/* ============================================================
 * lifecycle
 * ============================================================ */

c4_game_t c4_new_game(void) {
    return new c4_game();
}

void c4_free_game(c4_game_t g) {
    delete g;
}

/* ============================================================
 * mirror external move (your engine played a move)
 * ============================================================ */

void c4_pascal_play(c4_game_t g, int col) {
    assert(g);
    assert(g->pos.canPlay(col));

    g->pos.play(col);
}

/* ============================================================
 * Pascal chooses AND plays a move
 * ============================================================ */

int c4_pascal_best(c4_game_t g) {
    assert(g);

    Position& P = g->pos;
    Solver&   S = g->solver;

    /* 1. If Pascal can win immediately, do it */
    for (int col = 0; col < Position::WIDTH; ++col) {
        if (P.canPlay(col) && P.isWinningMove(col)) {
            P.play(col);
            return col;
        }
    }

    /*
     * 2. Solver precondition:
     *    negamax assumes the side to move
     *    cannot win on the next move.
     */
    assert(!P.canWinNext());

    /* 3. Analyze all moves */
    std::vector<int> scores = S.analyze(P);

    int bestCol   = -1;
    int bestScore = -1000000;

    for (int col = 0; col < Position::WIDTH; ++col) {
        if (!P.canPlay(col)) continue;
        if (scores[col] == Solver::INVALID_MOVE) continue;

        if (scores[col] > bestScore) {
            bestScore = scores[col];
            bestCol   = col;
        }
    }

    /* There must always be a legal move */
    assert(bestCol >= 0);

    P.play(bestCol);
    return bestCol;
}

/* ============================================================
 * queries
 * ============================================================ */

int c4_pascal_can_play(c4_game_t g, int col) {
    assert(g);
    return g->pos.canPlay(col);
}

int c4_pascal_is_terminal(c4_game_t g) {
    assert(g);
    return g->pos.canWinNext() ||
           g->pos.nbMoves() == Position::WIDTH * Position::HEIGHT;
}

} /* extern "C" */
