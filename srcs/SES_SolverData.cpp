#include "SES_SolverData.hpp"

void SES_SolverData::AddToExpression(SES_Variable var) {
	_variables.push_back(var);
}

std::ostream &operator<<(std::ostream &os, const SES_SolverData& solverData) {
	if (solverData.GetVariables().empty()) {
		os << "0 = 0";
	}
	else {
		std::vector<SES_Variable> vars = solverData.GetVariables();
		os << vars[0].GetCoefficient() << " * X^" << vars[0].GetDegree();

		for (int i = 1; i < vars.size(); i++) {
			if (vars[i].GetCoefficient() < 0) {
				os << " - " << vars[i].GetCoefficient() * -1 << " * X^" << vars[i].GetDegree();
			}
			else {
				os << " + " << vars[i].GetCoefficient() << " * X^" << vars[i].GetDegree();
			}
		}
	}
	return os;
}