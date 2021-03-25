#include "SES_SolverData.hpp"

void SES_SolverData::AddExpression(SES_Variable var) {
	auto cur = GetVarByDegree(var.GetDegree());

	if (cur == _variables.end())
		_variables.push_back(var);
	else {
		if (cur->GetCoefficient() + var.GetCoefficient() == 0)
			_variables.erase(cur);
		else
			*cur = SES_Variable(cur->GetCoefficient() + var.GetCoefficient(), cur->GetDegree());
	}
	std::cout << "Added to expr " << var << std::endl; //TODO del
}

std::vector<SES_Variable>::iterator SES_SolverData::GetVarByDegree(int degree) {
	auto comparator = [degree](const SES_Variable& var){ return var.GetDegree() == degree; };
	return std::find_if(_variables.begin(), _variables.end(), comparator);
}

std::ostream &operator<<(std::ostream &os, const SES_SolverData& solverData) {
	if (solverData.GetVariables().empty()) {
		os << "0 = 0";
	}
	else {
		std::vector<SES_Variable> vars = solverData.GetVariables();
		os << vars[0].GetCoefficient() << " * X^" << vars[0].GetDegree();
		for (int i = 1; i < vars.size(); i++)
			os << " " << vars[i];
		os << " = 0";
	}
	return os;
}