#include "utilities.hpp"

bool contains(const std::string& orig, const std::string& income) {
	std::size_t found = orig.find(income);

	if (found != std::string::npos)
		return true;
	return false;
}

double custom_sqrt(double number) {
	if (number < 0)
		return MY_NAN;
	if (number == 0)
		return 0;

	double low, high, mid;
	double tmp;

	if(number >= 1) {
		low = 1;
		high = number;
	}
	else {
		low = number;
		high = 1;
	}

	while(low <= high) {
		mid = (low + high) / 2.0;
		tmp = mid * mid;

		if (is_equally(tmp, number))
			return mid;

		if (tmp > number)
			high = mid;
		else
			low = mid;
	}
	return MY_NAN;
}

double n_zero_avoid(double number) {
	if (is_equally(number, -0.0))
		return 0.0;
	return number;
}
