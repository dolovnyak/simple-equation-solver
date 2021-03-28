#pragma once

#include <string>
#define MY_NAN 0.0 / 0.0

bool contains(const std::string& orig, const std::string& income);
double custom_sqrt(double number);

inline bool is_equally(double x, double y) {
	return x - y >= -0.0000001 && x - y <= 0.0000001;
}
