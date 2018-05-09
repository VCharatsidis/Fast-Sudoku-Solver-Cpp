#ifndef BOX_STRUCTURE_H
#define BOX_STRUCTURE_H
#include <vector>
#include "Box.cpp"
#include <unordered_map>
using std::vector;
using std::unordered_map;

class Box_Structure {
public:
	vector<Box*> structure_boxes;
	unordered_map<int, long> boxes_per_value;
	int id;

};

#endif