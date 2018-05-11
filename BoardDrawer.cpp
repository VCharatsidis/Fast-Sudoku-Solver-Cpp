#ifndef BOARDDRAWER_H
#define BOARDDRAWER_H
#include <array>;
#include <vector>;
#include <iostream>;
#include <string>;
#include <fstream>;

using std::vector;
using std::string;

class BoardDrawer {
public:
	const string file_path = "C:\\Users\\vcharatsidis\\Desktop\\sudoku.txt";
	const string horizontal_line_serparator = "-----------------------------------------------------------------------------------------";
	const string vertical_line_separator = "| ";
	const string empty_box = "_";

	void draw_board(vector<vector<int>> board) {
		int boardSize = board.size();
		int container_size = sqrt(boardSize);
		int horizontalLines = container_size-1;
		int drawHeight = boardSize + horizontalLines;
		int drawWidth = boardSize;

		std::ofstream myfile;
		myfile.open(file_path);

		int horizontal_line_counter = 0;

		for (int row = 0; row < drawHeight; row++) {
			bool drawHorizontalLine = ((row + 1) % (container_size+1) == 0);

			if (drawHorizontalLine) {
				myfile << horizontal_line_serparator;
				horizontal_line_counter++;
			}
			else {
				for (int column = 0; column < drawWidth; column++) {
					bool drawVerticalLine = (column % container_size == 0 && column > 0);

					if (drawVerticalLine) {
						myfile << vertical_line_separator;
					}

					int value = board[row - horizontal_line_counter][column];
					string valueToString = std::to_string(value);

					if (value == 0) {
						valueToString = empty_box;
					}
					string space = " ";
					if (boardSize > 9) {
						if (value < 10) {
							space += " ";
						}
					}
					myfile << valueToString + space;
				}
			}
			myfile << "\n";
		}
		myfile.close();
	}
};
#endif