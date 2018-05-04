#include <vector>;
using std::vector;

class SuperHard25x25 {
public:
	vector<vector<int>> return_board() {
		vector<vector<int>> hardestSudoku(25, vector<int>(25, 0));

		hardestSudoku[0][7] = 24;
		hardestSudoku[0][10] = 19;
		hardestSudoku[0][20] = 13;

		hardestSudoku[1][5] = 15;

		hardestSudoku[2][2] = 8;
		hardestSudoku[2][11] = 3;
		hardestSudoku[2][18] = 9;

		hardestSudoku[3][1] = 19;
		hardestSudoku[3][19] = 5;

		hardestSudoku[4][6] = 19;
		hardestSudoku[4][14] = 20;
		hardestSudoku[4][15] = 25;

		hardestSudoku[5][1] = 15;
		hardestSudoku[5][14] = 23;
		hardestSudoku[5][16] = 21;
		hardestSudoku[5][23] = 2;

		hardestSudoku[6][1] = 25;
		hardestSudoku[6][12] = 6;

		hardestSudoku[7][10] = 5;
		hardestSudoku[7][16] = 11;
		hardestSudoku[7][19] = 9;

		hardestSudoku[8][0] = 23;

		hardestSudoku[9][0] = 9;
		hardestSudoku[9][20] = 5;

		hardestSudoku[10][4] = 18;
		hardestSudoku[10][7] = 11;
		hardestSudoku[10][21] = 25;

		hardestSudoku[11][4] = 10;
		hardestSudoku[11][5] = 4;
		hardestSudoku[11][6] = 5;
		hardestSudoku[11][18] = 7;
		hardestSudoku[11][24] = 17;

		hardestSudoku[12][2] = 14;
		hardestSudoku[12][15] = 9;
		hardestSudoku[12][16] = 16;
		hardestSudoku[12][18] = 6;

		hardestSudoku[13][13] = 13;
		hardestSudoku[13][23] = 6;

		hardestSudoku[14][7] = 12;
		hardestSudoku[14][11] = 20;
		hardestSudoku[14][20] = 4;
		hardestSudoku[14][21] = 5;

		hardestSudoku[15][0] = 18;
		hardestSudoku[15][4] = 3;
		hardestSudoku[15][5] = 24;
		hardestSudoku[15][10] = 22;
		hardestSudoku[15][16] = 20;
		hardestSudoku[15][23] = 13;

		hardestSudoku[16][5] = 18;
		hardestSudoku[16][15] = 22;
		hardestSudoku[16][16] = 23;
		hardestSudoku[16][19] = 7;
		hardestSudoku[16][24] = 8;

		hardestSudoku[17][1] = 17;
		hardestSudoku[17][10] = 18;

		hardestSudoku[18][8] = 14;
		hardestSudoku[18][12] = 1;
		hardestSudoku[18][15] = 18;
		hardestSudoku[18][19] = 3;

		//hardestSudoku[19] is empty.

		hardestSudoku[20][0] = 3;
		hardestSudoku[20][2] = 4;
		hardestSudoku[20][5] = 6;
		hardestSudoku[20][13] = 12;
		hardestSudoku[20][21] = 2;

		hardestSudoku[21][1] = 10;
		hardestSudoku[21][13] = 16;
		hardestSudoku[21][16] = 22;

		//hardestSudoku[22] is empty.

		hardestSudoku[23][5] = 21;
		hardestSudoku[23][8] = 20;
		hardestSudoku[23][11] = 10;
		hardestSudoku[23][15] = 3;
		hardestSudoku[23][21] = 24;

		//hardestSudoku[24] is empty.
		
		return hardestSudoku;
	}
};