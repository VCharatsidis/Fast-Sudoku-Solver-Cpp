#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "Box.cpp"
#include "Box_structure.cpp"
#include "Row.cpp";
#include "Column.cpp";
#include "Container.cpp";

#include "Move.cpp";
#include <stack>;

#include <bitset>;
#include <queue>;
#include "Comparator.cpp";

using std::priority_queue;
using std::vector;

class Board {
public:
	vector<vector<Box*>> boxes;
	priority_queue<Box*, vector<Box*>, Comparator> most_constraint_box;
	vector<vector<int>> board;
	std::stack<Box*> moves_done;

	vector<Box_Structure*> rows;
	vector<Box_Structure*> columns;
	vector<Box_Structure*> containers;

	int container_size;
	int board_size;
	int starting_number_of_empty_squares;

	Board(vector<vector<int>> b) {
		board = b;
		board_size = b.size();
		container_size = sqrt(b.size());

		rows.reserve(board_size);
		make_rows();
		make_columns();
		make_containers();

		fill_row_structure_boxes_and_board_boxes();

		fill_column_structure_boxes();
		
		for (int row = 0; row < board_size; row++) {
			fill_boxes_per_value(rows[row]);
		}

		for (int column = 0; column < board_size; column++) {
			fill_boxes_per_value(columns[column]);
		}

		fill_container_structure_boxes();

		for (int container = 0; container < board_size; container++) {
			fill_boxes_per_value(containers[container]);
		}

		make_most_constraint_box();
	}

	void fill_row_structure_boxes_and_board_boxes() {
		for (int row = 0; row < board_size; row++) {
			vector<Box*> current;

			for (int column = 0; column < board_size; column++) {
				current.push_back(create_box(row, column, board[row][column]));
			}

			rows[row]->structure_boxes = current;
			boxes.push_back(current);
		}
	}

	void make_rows() {
		for (int row = 0; row < board_size; row++) {
			Box_Structure* row_structure = new Row();

			for (int value = 1; value < board_size + 1; value++) {
				row_structure->boxes_per_value.insert({ value,  0b1111111111111111111111111 });
			}

			rows.push_back(row_structure);
		}
		
	}

	void make_columns() {
		for (int column = 0; column < board_size; column++) {
			Box_Structure* column_structure = new Column();

			for (int value = 1; value < board_size + 1; value++) {
				column_structure->boxes_per_value.insert({ value, 0b1111111111111111111111111 });
			}

			columns.push_back(column_structure);
		}
	}

	void make_containers() {
		for (int container = 0; container < board_size; container++) {
			Box_Structure* container_structure = new Container();

			for (int value = 1; value < board_size + 1; value++) {
				container_structure->boxes_per_value.insert({ value,  0b1111111111111111111111111 });
			}

			containers.push_back(container_structure);
		}
	}

	void fill_column_structure_boxes() {
		for (int column = 0; column < board_size; column++) {
			vector<Box*> current;

			for (int row = 0; row < board_size; row++) {
				current.push_back(rows[row]->structure_boxes[column]);
			}

			columns[column]->structure_boxes = current;
		}
	}

	void fill_container_structure_boxes() {
		int container_counter = 0;

		for (int container_x = 0; container_x < board_size; container_x += container_size) {
			for (int container_y = 0; container_y < board_size; container_y += container_size) {
				vector<Box*> current;

				int end_row = container_x + container_size;
				int end_column = container_y + container_size;

				for (int row = container_x; row < end_row; row++) {
					for (int column = container_y; column < end_column; column++) {
						current.push_back(rows[row]->structure_boxes[column]);
					}
				}

				containers[container_counter]->structure_boxes = current;
				container_counter++;
			}
		}
	}

	void fill_boxes_per_value(Box_Structure* structure) {
		for (int box = board_size-1; box >= 0; box--) {
			int box_value = structure->structure_boxes[box]->value;

			if (box_value == 0) {
				structure->boxes_per_value[box_value] = 0b0000000000000000000000000;
			}

			for (int value = 1; value < board_size + 1; value++) {
				if (box_value == 0) {
					long available_values = structure->structure_boxes[box]->available_values;
					long value_to_long = 1 << value;
					long intersection = value_to_long & available_values;
					bool value_is_not_available = (intersection == 0);

					if (value_is_not_available) {
						remove_box(structure, value, box);
					}
					
				}
				else {
					remove_box(structure, value, box);
				}
			}	
		}
	}

	void remove_box(Box_Structure* structure, int value, int box) {
		long av_boxes = structure->boxes_per_value.at(value);
		long box_to_long = 1 << box;

		structure->boxes_per_value[value] = av_boxes & ~box_to_long;
	}

	void update_boxes(Box_Structure* structure, int value) {
		long boxes = structure->boxes_per_value.at(value);
		long value_to_binary_long = 1 << value;
		long updated_boxes = boxes | value_to_binary_long;

		structure->boxes_per_value[value] = updated_boxes;
	}

	Box* create_box(int row, int column, int value) {
		Box* box = new Box(row, column);

		if (value == 0) {
			box->value = 0;
			update_available_values(box);
		}
		else {
			starting_number_of_empty_squares++;
			box->value = value;
			box->available_values = 0;
		}

		return box;
	}

	void update_available_values(Box* box) {
		int row = box->row;
		int column = box->column;

		long constrained_values = 0b000000000000000000000000;

		//row constraints
		for (int col = 0; col < board_size; col++) {
			if (board[row][col] != 0) {
				long v = 1 << board[row][col];
				constrained_values |= v;
			}
		}
		//column constraints;
		for (int r = 0; r < board_size; r++) {
			if (board[r][column] != 0) {
				long v = 1 << board[r][column];
				constrained_values |= v;
			}
		}
		//container constraints
		int* container_coords = find_container_starting_box(row, column);
		int start_row = container_coords[0];
		int start_column = container_coords[1];
		int end_row = container_coords[0] + container_size;
		int end_column = container_coords[1] + container_size;

		for (int r = start_row; r < end_row; r++) {
			for (int col = start_column; col < end_column; col++) {
				if (board[r][col] != 0) {
					long v = 1 << board[r][col];
					constrained_values |= v;
				}
			}
		}
		
		box->available_values = ~constrained_values;
	}

	int* find_container_starting_box(int row, int column) {
		int container_x = row / container_size;
		int container_y = column / container_size;

		int starting_box_x = container_x * container_size;
		int starting_box_y = container_y * container_size;

		int coords[] = { starting_box_x, starting_box_y };
		return coords;
	}

	void make_most_constraint_box() {
		most_constraint_box = priority_queue<Box*, vector<Box*>, Comparator>();
		for (int row = 0; row < board_size; row++) {
			for (int column = 0; column < board_size; column++) {
				if (board[row][column] == 0) {
					most_constraint_box.push(boxes[row][column]);
				}	
			}
		}
	}

	bool game_over() {
		int moves_played = moves_done.size();
		bool game_over = (moves_played == board_size - starting_number_of_empty_squares);

		if (game_over) {
			return true;
		}
		else {
			return false;
		}
	}

	void play_move(Box* box) {
		moves_done.push(box);
		int box_row = box->row;
		int box_col = box->column;
		int value = box->value;

		boxes[box_row][box_col]->value = value;
		board[box_row][box_col] = value;
		
		for (int row = 0; row < board_size; row++) {
			for (int column = 0; column < board_size; column++) {
				update_available_values(boxes[row][column]);
			}
		}

		make_most_constraint_box();

	}

	void undo_move() {
		int box_row = moves_done.top()->row;
		int box_col = moves_done.top()->column;
		moves_done.pop();
		boxes[box_row][box_col]->value = 0;
		board[box_row][box_col] = 0;

		for (int row = 0; row < board_size; row++) {
			for (int column = 0; column < board_size; column++) {
				update_available_values(boxes[row][column]);
			}
		}

		make_most_constraint_box();
	}

};

#endif