#include <vector>
using std::vector;

struct Box {
public:

	Box(int i, int j) {
		row = i;
		column = j;
	}

    vector<Box*> row_boxes;
	vector<Box*> column_boxes;
	vector<Box*> container_boxes;

	int row;
	int column;

	long available_values;
	long value;

};