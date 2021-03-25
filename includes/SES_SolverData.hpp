#pragma once

#include <vector>
#include "SES_Variable.hpp"

class SES_SolverData {
public:
	void AddExpression(SES_Variable var);

	std::vector<SES_Variable> GetVariables() const {return _variables;}

private:
	std::vector<SES_Variable> _variables;

	std::vector<SES_Variable>::iterator GetVarByDegree(int degree);
};

std::ostream &operator<<(std::ostream &os, const SES_SolverData& solverData);
