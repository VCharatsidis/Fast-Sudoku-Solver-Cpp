#include "Board.cpp";
#include "BoardDrawer.cpp";

using std::cout;
using std::endl;

class Solver {
public:
	int size;
	Board* to_solve;
	int steps = 0;

	Solver(Board* board) {
		to_solve = board;
		size = board->board_size;
		
	};

	void solve() {
		bool game_over = to_solve->game_over();

		if (game_over) {
			int avg_brunching_factor = ((to_solve->choises) / steps);
			cout << "avg brunching factor "+std::to_string(avg_brunching_factor)<<endl; 
			cout << std::to_string(steps) << endl;
			BoardDrawer* drawer = new BoardDrawer();
			drawer->draw_board(to_solve->board);
			return;
		}
	
		Box* constraint_box = to_solve->find_most_constraint_box();

		if (constraint_box->available_values == 0) {
			cout << "unsolvable";
			BoardDrawer* drawer = new BoardDrawer();
			drawer->draw_board(to_solve->board);
			return;
		}

		
		long available_values = constraint_box->available_values;
		to_solve->choises += to_solve->number_of_ones(available_values);

		for (int value = 1; value < size+1; value++) {
			long long_value = 1 << value;
			
			bool value_is_available = ((available_values & long_value) != 0);

			if (value_is_available) {
				constraint_box->value = value;
				constraint_box->available_values = 0;

				to_solve->play_move(constraint_box);
				steps++;

				if (steps % 1000 == 0) {
					cout << std::to_string(steps) << endl;
					BoardDrawer* drawer = new BoardDrawer();
					drawer->draw_board(to_solve->board);
				}

				solve();

				game_over = to_solve->game_over();

				if (game_over) {
					int avg_brunching_factor = ((to_solve->choises) / steps);
					cout << "avg brunching factor " + std::to_string(avg_brunching_factor) << endl;
					cout << std::to_string(steps) << endl;
					BoardDrawer* drawer = new BoardDrawer();
					drawer->draw_board(to_solve->board);
					return;
				}
				else {
					to_solve->undo_move();
					constraint_box->value = 0;
					constraint_box->available_values = available_values;
				}
			}
		}
	}
};
