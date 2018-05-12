
#include "Sudoku25x25.cpp";
//#include "EasySudoku.cpp";
#include "BoardDrawer.cpp";
#include <iostream>;
#include <string>;
#include <queue>;
#include "Comparator.cpp";
#include <bitset>;
#include "Board.cpp";
#include "Solver.cpp";

using std::priority_queue;
using std::cout;

void print_values(const long values) {
	
	for (size_t i = 0; i < CHAR_BIT * sizeof values; ++i)
	{
		if ((values & (1 << i)) != 0) {
			cout <<"av values "+ std::to_string(i) +" " ;
		}
	}
	cout << "" << std::endl;
}

int main() {
	
	SuperHard25x25 sh;
	//EasySudoku es;

	vector<vector<int>> hardestSudoku = sh.return_board();

	BoardDrawer* drawer = new BoardDrawer();
	drawer->draw_board(hardestSudoku);

	//Test Drawer
	/*Board* drawboard = new Board(hardestSudoku);
	Box* move = new Box(11,16);
	move->value = 1;
	drawboard->play_move(move);
	drawer->draw_board(drawboard->board);*/

	Board board = Board(hardestSudoku);
	long av_values = board.boxes[20][10]->available_values;
	int val = board.boxes[20][10]->value;

	cout <<  std::bitset<26>(av_values) << std::endl;
	cout << "value "+std::to_string(val) << std::endl;
	print_values(av_values);

	////Test row structures
	//cout << "Test box structures " << std::endl;
	//cout << std::to_string(board.rows.size()) << std::endl;
	//for (int i = 0; i < board.rows.size(); i++) {
	//	cout << "row " + std::to_string(i)<< std::endl;
	//	for (int j = 1; j <  board.rows.size() + 1; j++) {
	//		cout << "value " + std::to_string(j) +" ";
	//		cout << std::bitset<25>(board.rows[i]->boxes_per_value.at(j)) << std::endl; 
	//	}
	//}
	//cout << " " << std::endl;

	////Test column structures
	//cout << "Test column structures " << std::endl;
	//cout << std::to_string(board.columns.size()) << std::endl;
	//for (int i = 0; i < board.columns.size(); i++) {
	//	cout << "column " + std::to_string(i) << std::endl;
	//	for (int j = 1; j < board.columns.size() + 1; j++) {
	//		cout << "value " + std::to_string(j) + " ";
	//		cout << std::bitset<25>(board.columns[i]->boxes_per_value.at(j)) << std::endl;
	//	}
	//}
	//cout << " " << std::endl;

	////Test container structures
	//cout << "Test container structures " << std::endl;
	//cout << std::to_string(board.columns.size()) << std::endl;
	//for (int i = 0; i < board.containers.size(); i++) {
	//	cout << "container " + std::to_string(i) << std::endl;
	//	for (int j = 1; j < board.containers.size() + 1; j++) {
	//		cout << "value " + std::to_string(j) + " ";
	//		cout << std::bitset<25>(board.containers[i]->boxes_per_value.at(j)) << std::endl;
	//	}
	//}
	//cout << " " << std::endl;

	//Test solver
	Board* hardboard = new Board(hardestSudoku);
	for (int i = 0; i < hardboard->board.size(); i++) {
		for (int j = 0; j < hardboard->board.size(); j++) {
			std::cout << "box " + std::to_string(i) + "," + std::to_string(j) << std::endl;
			std::cout << std::bitset<25>(hardboard->boxes[i][j]->available_values) << std::endl;
		}
	}

	Solver* solver = new Solver(hardboard);
	solver->solve();

	return 0;
};