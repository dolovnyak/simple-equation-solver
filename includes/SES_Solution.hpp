#pragma once

#include "string"

class SES_Solution {
public:
	SES_Solution();

	void AddSolutionString(const std::string& solutionString);
	[[nodiscard]] std::string ToString() const;

private:
	std::string _stringSolution;
};

std::ostream &operator<<(std::ostream &os, const SES_Solution& solution);
