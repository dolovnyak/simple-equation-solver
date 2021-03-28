#pragma once

#include <vector>
#include "SES_Variable.hpp"

class SES_SolverData {
public:
	void AddExpression(SES_Variable var);
	void SubExpression(SES_Variable var);

	[[nodiscard]] std::vector<SES_Variable> GetVariables() const;
	[[nodiscard]] int GetMaxDegree() const;
	[[nodiscard]] std::string ToString() const;
	[[nodiscard]] bool IsDegreeCorrect() const;
	[[nodiscard]] double GetCoefficientByDegree(int degree) const;

private:
	std::vector<SES_Variable> _variables;

	std::vector<SES_Variable>::iterator GetVarByDegree(int degree);
};

std::ostream &operator<<(std::ostream &os, const SES_SolverData& solverData);
