#include "utilities.hpp"

bool contains(const std::string& orig, const std::string& income)
{
	std::size_t found = orig.find(income);

	if (found != std::string::npos)
		return true;
	return false;
}