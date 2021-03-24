#pragma once

#include <vector>
#include "SES_Variable.hpp"

class SES_SolverData {
public:
	void AddToExpression(SES_Variable var);

	std::vector<SES_Variable> GetVariables() const {return _variables;}

private:
	std::vector<SES_Variable> _variables;
};

std::ostream &operator<<(std::ostream &os, const SES_SolverData& solverData);
