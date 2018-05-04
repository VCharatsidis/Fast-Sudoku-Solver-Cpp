#pragma once
#include <vector>;
#include <string>;
#include <stack>;
#include "SudokuMove.cpp";

using std::vector;
using std::string;
using std::stack;

class Board {
public:
	static vector<vector<int>> board;
	static int sudoku_size;
	
	Board(vector<vector<int>> board);
	static void play_move(SudokuMove* move);
	static void undo_move();
	static bool is_empty(Box box);
	static bool is_move_valid(SudokuMove move);
	static bool game_over();
	
private:
	static int starting_number_of_empty_squares;
	static stack<SudokuMove*> moves_done;

	static void assign_value(Box box, int value);
	static bool is_value_valid(vector<int> box_structure, int value);
	static Box find_container_starting_box(Box box);
	static vector<int> gather_column_boxes(int given_column);
	static vector<int> gather_container_boxes(Box box);
	static bool is_value_valid_in_container(SudokuMove move);
	static int starting_number_empty_sqaures();
	static void print_stack(stack<SudokuMove*> c);
};



