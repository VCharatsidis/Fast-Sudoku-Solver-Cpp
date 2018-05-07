#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "Box.cpp"

using std::vector;

class Board {
public:
	vector<vector<Box*>> boxes;
	vector<vector<int>> board;
	int container_size;

	Board(vector<vector<int>> b) {
		board = b;
		container_size = sqrt(b.size());

		for (int row = 0; row < b.size(); row++) {
			vector<Box*> current;
			for (int column = 0; column < b[0].size(); column++) {
				current.push_back(create_box(row, column, b[row][column]));
			}
			boxes.push_back(current);
		}
	}

	Box* create_box(int row, int column, int value) {
		Box* box = new Box(row, column);

		if (value == 0) {
			box->value = 0;
			update_available_values(box);
		}
		else {
			box->value = value;
			box->available_values = 0;
		}

		return box;
	}

	void update_available_values(Box* box) {
		int row = box->row;
		int column = box->column;
		long values = 0b0000000000000000000000000;

		for (int col = 0; col < board.size(); col++) {
			if (board[row][col] != 0) {
				long v = 1 << board[row][col];
				values |= v;
			}
		}

		for (int r = 0; r < board.size(); r++) {
			if (board[r][column] != 0) {
				long v = 1 << board[r][column];
				values |= v;
			}
		}

		int* container_coords = find_container_starting_box(row, column);
		int start_row = container_coords[0];
		int start_column = container_coords[1];
		int end_row = container_coords[0] + container_size;
		int end_column = container_coords[1] + container_size;

		for (int r = start_row; r < end_row; r++) {
			for (int col = start_column; col < end_column; col++) {
				if (board[r][col] != 0) {
					long v = 1 << board[r][col];
					values |= v;
				}
			}
		}

		box->available_values = values;
	}

	int* find_container_starting_box(int row, int column) {
		int container_x = row / container_size;
		int container_y = column / container_size;

		int starting_box_x = container_x * container_size;
		int starting_box_y = container_y * container_size;

		int coords[] = { starting_box_x, starting_box_y };
		return coords;
	}
};

#endif