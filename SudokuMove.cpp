#include "Box.cpp"
#include <iostream>;

struct SudokuMove{
	Box* box;
	int value;
	~SudokuMove() {};
};