#include <vector>
#include "Box.cpp"
#include <unordered_map>
using std::vector;
using std::unordered_map;

class Box_Structure {
public:
	vector<Box*> boxes;
	unordered_map<int, long> boxes_per_value;
	int id;

	void update() {

	}

	Box* find_most_constrained() {

	}

};