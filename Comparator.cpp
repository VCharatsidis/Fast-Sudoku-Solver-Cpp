#include "Box.cpp"

class Comparator {
public:
	Comparator(){

	}
	Box* operator() (Box* a, Box* b) {
		long values_a = a->available_values;
		long values_b = b->available_values;

		int non_zero_values_a = available_values(values_a);
		int non_zero_values_b = available_values(values_b);

		if (non_zero_values_a > non_zero_values_b) {
			return a;
		}
		else {
			return b;
		}
	}

private:
	int available_values(long available_values) {
		size_t num_zeroes = 0;

		for (size_t i = 0; i < CHAR_BIT * sizeof available_values; ++i)
		{
			if ((available_values & (1 << i)) == 1)
				++num_zeroes;
		}

		return num_zeroes;
	}
};