
#include "Sudoku25x25.cpp";
//#include "EasySudoku.cpp";
#include "BoardDrawer.cpp";
#include <iostream>;
#include <string>;
#include <queue>
#include "Comparator.cpp";
#include <bitset>

using std::priority_queue;
using std::cout;

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
	//Box e = Box(3, 7);

	a.available_values = 0b1011;
	b.available_values = 0b100000000000000000001;
	c.available_values = 0b1111;
	d.available_values = 0b1;
	//e.available_values = 0b01111111111;

	pq.push(a);
	pq.push(b);
	pq.push(c);
	pq.push(d);
	//pq.push(e);

	while (!pq.empty()) {
		Box k = pq.top();
		cout << std::bitset<25>(k.available_values) << std::endl;
		pq.pop();
	}

	return 0;
};