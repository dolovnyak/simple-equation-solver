#include "SES_SolverData.hpp"

void SES_SolverData::AddExpression(SES_Variable var) {
	auto cur = GetVarByDegree(var.GetDegree());

	if (var.GetCoefficient() == 0)
		return;

	if (cur == _variables.end())
		_variables.push_back(var);
	else {
		if (cur->GetCoefficient() + var.GetCoefficient() == 0)
			_variables.erase(cur);
		else
			*cur = SES_Variable(cur->GetCoefficient() + var.GetCoefficient(), cur->GetDegree());
	}
}

void SES_SolverData::SubExpression(SES_Variable var) {
	AddExpression(var * SES_Variable(-1, 0));
}

std::vector<SES_Variable>::iterator SES_SolverData::GetVarByDegree(int degree) {
	auto comparator = [degree](const SES_Variable& var){ return var.GetDegree() == degree; };
	return std::find_if(_variables.begin(), _variables.end(), comparator);
}

std::string SES_SolverData::ToString() const {
	std::ostringstream oss;

	if (this->GetVariables().empty()) {
		oss << "0 = 0";
	}
	else {
		std::vector<SES_Variable> vars = this->GetVariables();
		oss << vars[0].GetCoefficient() << " * X^" << vars[0].GetDegree();
		for (int i = 1; i < vars.size(); i++)
			oss << " " << vars[i];
		oss << " = 0";
	}
	return oss.str();
}

std::vector<SES_Variable> SES_SolverData::GetVariables() const {
	return _variables;
}

std::ostream &operator<<(std::ostream &os, const SES_SolverData& solverData) {
	os << solverData.ToString();
	return os;
}