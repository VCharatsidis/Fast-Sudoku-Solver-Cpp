#include "Box.cpp"
#include <vector>

class Comparator {
public:
	
	bool operator() (const Box& a, const Box& b) const {
		int zv_a = available_values(a.available_values);
		int zv_b = available_values(b.available_values);

		return zv_a < zv_b;
	}

private:
	int available_values(long available_values) const {
		size_t num_zeroes = 0;

		for (size_t i = 0; i < CHAR_BIT * sizeof available_values; ++i)
		{
			if ((available_values & (1 << i)) == 0)
				++num_zeroes;
		}

		return num_zeroes;
	}
};