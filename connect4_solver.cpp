#include "connect4_solver.h"
#include "Position.hpp"
#include "Solver.hpp"

struct C4Wrapper {
    Position position;
};

extern "C" {

c4_position_t c4_create() {
    return new C4Wrapper();
}

void c4_destroy(c4_position_t pos) {
    delete static_cast<C4Wrapper*>(pos);
}

int c4_can_play(c4_position_t pos, int col) {
    auto* p = static_cast<C4Wrapper*>(pos);
    return p->position.canPlay(col);
}

void c4_play(c4_position_t pos, int col) {
    auto* p = static_cast<C4Wrapper*>(pos);
    p->position.play(col);
}

int c4_best_move(c4_position_t pos) {
    auto* p = static_cast<C4Wrapper*>(pos);

    Solver solver;
    int best_col = -1;
    int best_score = -100;

    for (int col = 0; col < Position::WIDTH; col++) {
        if (!p->position.canPlay(col)) continue;

        Position next = p->position;
        next.play(col);

        int score = -solver.negamax(next, -Position::HEIGHT * Position::WIDTH,
                                    Position::HEIGHT * Position::WIDTH);

        if (score > best_score) {
            best_score = score;
            best_col = col;
        }
    }

    return best_col;
}

int c4_solve(c4_position_t pos) {
    auto* p = static_cast<C4Wrapper*>(pos);
    Solver solver;
    return solver.solve(p->position);
}

}
