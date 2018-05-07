#include <vector>
using std::vector;

struct Box {
public:
	const vector<Box*> row_boxes;
	const vector<Box*> column_boxes;
	const vector<Box*> container_boxes;

	int row;
	int column;

	long available_values;
	long value;

	Box() {

	}
};