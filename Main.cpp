
#include "Sudoku25x25.cpp";
//#include "EasySudoku.cpp";
#include "BoardDrawer.cpp";
#include <iostream>;
#include <string>;
#include <queue>;
#include "Comparator.cpp";
#include <bitset>;
#include "Board.cpp";

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

	//check solver
	priority_queue<Box, vector<Box>, Comparator> pq;

	Box a = Box(1,2);
	Box b = Box(2,3);
	Box c = Box(3,4);
	Box d = Box(4,5);

	a.available_values = 0b1011;
	b.available_values = 0b100000000000000000001;
	c.available_values = 0b1111;
	d.available_values = 0b1;

	pq.push(a);
	pq.push(b);
	pq.push(c);
	pq.push(d);

	while (!pq.empty()) {
		Box k = pq.top();
		cout << std::bitset<25>(k.available_values) << std::endl;
		pq.pop();
	}

	Board board = Board(hardestSudoku);
	long av_values = board.boxes[20][10]->available_values;
	int val = board.boxes[20][10]->value;

	cout <<  std::bitset<26>(av_values) << std::endl;
	cout << "value "+std::to_string(val) << std::endl;
	print_values(av_values);

	//Test row structures
	cout << "Test box structures " << std::endl;
	cout << std::to_string(board.rows.size()) << std::endl;
	for (int i = 0; i < board.rows.size(); i++) {
		cout << "row " + std::to_string(i)<< std::endl;
		for (int j = 1; j <  board.rows.size() + 1; j++) {
			cout << "value " + std::to_string(j) +" ";
			cout << std::bitset<25>(board.rows[i]->boxes_per_value.at(j)) << std::endl; 
		}
	}
	cout << " " << std::endl;

	//Test column structures
	cout << "Test column structures " << std::endl;
	cout << std::to_string(board.columns.size()) << std::endl;
	for (int i = 0; i < board.columns.size(); i++) {
		cout << "column " + std::to_string(i) << std::endl;
		for (int j = 1; j < board.columns.size() + 1; j++) {
			cout << "value " + std::to_string(j) + " ";
			cout << std::bitset<25>(board.columns[i]->boxes_per_value.at(j)) << std::endl;
		}
	}
	cout << " " << std::endl;

	//Test container structures
	cout << "Test container structures " << std::endl;
	cout << std::to_string(board.columns.size()) << std::endl;
	for (int i = 0; i < board.containers.size(); i++) {
		cout << "container " + std::to_string(i) << std::endl;
		for (int j = 1; j < board.containers.size() + 1; j++) {
			cout << "value " + std::to_string(j) + " ";
			cout << std::bitset<25>(board.containers[i]->boxes_per_value.at(j)) << std::endl;
		}
	}
	cout << " " << std::endl;

	return 0;
};