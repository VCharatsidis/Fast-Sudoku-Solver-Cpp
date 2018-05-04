#include <vector>
#include "Box.cpp"
#include <unordered_map>
using std::vector;
using std::unordered_map;

class Box_Structure {
public:
	const vector<Box*> boxes;
	unordered_map<int, vector<Box*>> boxes_per_value;
	int id;

	void update() {

	}

	Box* find_most_constrained() {

	}

};