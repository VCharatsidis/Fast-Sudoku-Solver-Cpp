#include <iostream>;
struct Box {
	int row;
	int column;

	Box(int x, int y) {
		row = x;
		column = y;
		
	}
	~Box() { };
};