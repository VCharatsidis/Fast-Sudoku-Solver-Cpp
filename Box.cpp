#include <vector>
using std::vector;

struct Box {
public:
	const vector<Box*> row_boxes;
	const vector<Box*> column_boxes;
	const vector<Box*> container_boxes;

	const int row;
	const int column;

	long available_values;
	long value;
};