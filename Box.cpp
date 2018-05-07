#include <vector>
using std::vector;

struct Box {
public:

	Box(int i, int j) {
		row = i;
		column = j;
	}

	int row;
	int column;

	long available_values;
	int value;

};