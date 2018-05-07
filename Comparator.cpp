#include "Box.cpp"

class Comparator {
public:
	Comparator(){

	}
	bool operator() (Box& a, Box& b) {
		long values_a = a.available_values;
		long values_b = b.available_values;

		int zv_a = available_values(values_a);
		int zv_b = available_values(values_b);

		return zv_a < zv_b;
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