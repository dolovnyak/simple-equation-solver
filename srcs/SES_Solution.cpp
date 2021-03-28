#include "SES_Solution.hpp"

std::string SES_Solution::ToString() const {
	return _stringSolution;
}

SES_Solution::SES_Solution() : _stringSolution("") {}

void SES_Solution::AddSolutionString(const std::string& solutionString) {
	_stringSolution.append(solutionString);
	_stringSolution.append("\n");
}

std::ostream &operator<<(std::ostream &os, const SES_Solution& solution) {
	os << solution.ToString();
	return os;
}
