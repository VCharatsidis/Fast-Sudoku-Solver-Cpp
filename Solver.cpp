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
			BoardDrawer* drawer = new BoardDrawer();
			drawer->draw_board(to_solve->board);
			return;
		}
	
		Box* constraint_box = to_solve->most_constraint_box.top();
		//cout << to_solve->most_constraint_box.size() << endl;
		to_solve->most_constraint_box.pop();

		if (constraint_box->available_values == 0) {
			cout << "unsolvable";
			BoardDrawer* drawer = new BoardDrawer();
			drawer->draw_board(to_solve->board);
			return;
		}

		
		long available_values = constraint_box->available_values;

		//cout << std::bitset<26>(to_solve->most_constraint_box.top()->available_values) << std::endl;
		
		/*while (!to_solve->most_constraint_box.empty()) {
			Box* k = to_solve->most_constraint_box.top();
			cout << "Box: " + std::to_string(k->row) + "," + std::to_string(k->column) << std::endl;
			cout << std::bitset<25>(k->available_values) << std::endl;
			to_solve->most_constraint_box.pop();
		}*/

		for (int value = 1; value < size+1; value++) {
			long long_value = 1 << value;
			/*cout << "constraint_box " + std::to_string(constraint_box->row) + "," + std::to_string(constraint_box->column) << std::endl;
			cout << "long value" << endl;
			cout << std::bitset<27>(long_value) << std::endl;
			cout << "available values" << endl;
			cout << std::bitset<27>(available_values) << std::endl;
			cout << "long value + avaialbe value" << endl;
			cout << std::bitset<27>(available_values & long_value) << std::endl;*/
			bool value_is_available = ((available_values & long_value) != 0);
			//cout << std::to_string(value_is_available) << std::endl;

			if (value_is_available) {
				constraint_box->value = value;
				constraint_box->available_values = 0;

				to_solve->play_move(constraint_box);
				/*cout << "moves done " + std::to_string(to_solve->moves_done.size()) << endl;
				cout << "draw value " + std::to_string(value) << endl;*/
				BoardDrawer* drawer = new BoardDrawer();
				drawer->draw_board(to_solve->board);
				steps++;

				if (steps % 1000 == 0) {
					cout << std::to_string(steps) << endl;
					BoardDrawer* drawer = new BoardDrawer();
					drawer->draw_board(to_solve->board);
				}

				solve();

				game_over = to_solve->game_over();

				if (game_over) {
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
