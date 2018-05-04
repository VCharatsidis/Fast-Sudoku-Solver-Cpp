#include "Board.h";
#include <math.h>;
#include "Scores.h";
#include <string>;
#include <iostream>;

int empty_box_value = 0;
int container_size;

int Board::sudoku_size;
int Board::starting_number_of_empty_squares;
vector<vector<int>> Board::board;
stack<SudokuMove*> Board::moves_done;

Board::Board(vector<vector<int>> board) {
	sudoku_size = board.size();
	container_size = sqrt(sudoku_size);
	Board::board = board;	
	starting_number_of_empty_squares = starting_number_empty_sqaures();
}

int Board::starting_number_empty_sqaures() {
	int starting_number_empty = 0;

	for (int row = 0; row < sudoku_size; row++) {
		for (int column = 0; column < sudoku_size; column++) {
			if (Board::board[row][column] == empty_box_value) {
				starting_number_empty++;
			}
		}
	}

	return starting_number_empty;
}

void Board::assign_value(Box box, int value) {
	Board::board[box.row][box.column] = value;
}

void Board::play_move(SudokuMove* move) {
	int value = move->value;
	assign_value(*move->box, value);
	Board::moves_done.push(move);
}

void Board::print_stack(stack<SudokuMove*> c) {
	std::cout << "" << std::endl;
	while (!c.empty()) {
		SudokuMove m = *c.top();
		Box b = *m.box;
		int x = b.row;
		int y = b.column;
		std::cout << std::to_string(x) + ", " + std::to_string(y) + " value " + std::to_string(m.value) + "||";
		c.pop();
	}
	std::cout << "" << std::endl;
}

void Board::undo_move() {
	SudokuMove move_to_undo = *Board::moves_done.top();
	assign_value(*move_to_undo.box, empty_box_value);
	Board::moves_done.pop();	
}

bool Board::is_empty(Box box) {
	return Board::board[box.row][box.column] == empty_box_value;
}

bool Board::is_move_valid(SudokuMove move) {
	int row = move.box->row;
	int column = move.box->column;
	int value = move.value;

	bool valid_row = is_value_valid(board[row], value);

	if (valid_row) {
		bool valid_container = is_value_valid_in_container(move);

		if (valid_container) {
			
			vector<int> column_boxes = gather_column_boxes(column);
			bool valid_column = is_value_valid(column_boxes, value);
			return valid_column;
		}
	}
	return false;
}

bool Board::is_value_valid_in_container(SudokuMove move) {
	int value = move.value;
	Box box = find_container_starting_box(*move.box);
	vector<int> container_boxes = gather_container_boxes(box);
	bool is_valid_container = is_value_valid(container_boxes, value);

	return is_valid_container;
}

vector<int> Board::gather_column_boxes(int given_column) {
	vector<int> column_boxes;

	for(int row = 0; row < sudoku_size; row++) {
		column_boxes.push_back(Board::board[row][given_column]);
	}

	return column_boxes;
}

vector<int> Board::gather_container_boxes(Box starting_box) {
	vector<int> container_boxes;

	int start_row = starting_box.row;
	int end_row = start_row + container_size;
	int start_column = starting_box.column;
	int end_column = start_column + container_size;

	for (int x = start_row; x < end_row; x++) {
		for (int y = start_column; y < end_column; y++) {
			container_boxes.push_back(Board::board[x][y]);
		}
	}

	return container_boxes;
}

bool Board::is_value_valid(vector<int> box_structure, int value) {
	int box_structure_size = box_structure.size();

	for (int box = 0; box < box_structure_size; box++) {
		int box_value = box_structure[box];
		bool is_not_valid = (box_value == value);

		if (is_not_valid) {
			return false;
		}	
	}

	return true;
}

Box Board::find_container_starting_box(Box box) {	
	int container_x = box.row/container_size;
	int container_y = box.column/container_size;

	int starting_box_x = container_x * container_size;
	int starting_box_y = container_y * container_size;

	Box starting_box = Box(starting_box_x, starting_box_y);
	return starting_box;
}

bool Board::game_over() {
	int moves_played = moves_done.size();
	bool game_over = (moves_played == starting_number_of_empty_squares);

	if (game_over) {
		return true;
	}
	else {
		return false;
	}
}
 






