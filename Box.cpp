#ifndef BOX_H
#define BOX_H
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

#endif