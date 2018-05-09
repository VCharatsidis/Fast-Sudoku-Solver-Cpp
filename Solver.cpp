#include "Board.cpp";
#include "BoardDrawer.cpp";
#include "Move.cpp";

class Solver {
public:
	int size;
	Board* to_solve;
	int steps = 0;

	Solver::Solver(Board* board) {
		to_solve = board;
		size = board->board_size;
	};

	void Solver::solve() {
		bool game_over = to_solve->game_over();

		if (game_over) {
			BoardDrawer* drawer = new BoardDrawer();
			drawer->draw_board(to_solve->board);
			return;
		}

		
	}
};
