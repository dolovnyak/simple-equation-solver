#include "SES_Variable.hpp"

SES_Variable::SES_Variable(double coefficient, int degree) : _coefficient(coefficient), _degree(degree) {
	if (!isCorrect())
		throw std::runtime_error("degree is incorrect"); //TODO make custom exceptions
}

SES_Variable SES_Variable::operator*(const SES_Variable& var) const {
	SES_Variable newVar(_coefficient * var._coefficient, _degree + var._degree);
	if (!newVar.isCorrect())
		throw std::runtime_error("degree is incorrect"); //TODO make custom exceptions
	return newVar;
}

SES_Variable SES_Variable::operator/(const SES_Variable& var) const {
	SES_Variable newVar(_coefficient / var._coefficient, _degree - var._degree);
	if (!newVar.isCorrect())
		throw std::runtime_error("degree is incorrect"); //TODO make custom exceptions
	return newVar;
}

bool SES_Variable::isCorrect() {
	if (_degree >= 0 && _degree <= 2)
		return true;
	return false;
}

double SES_Variable::GetCoefficient() const {
	return _coefficient;
}

int SES_Variable::GetDegree() const {
	return _degree;
}

std::ostream &operator<<(std::ostream &os, const SES_Variable& var) {
	if (var.GetCoefficient() < 0)
		os << "- " << var.GetCoefficient() * -1 << " * X^" << var.GetDegree();
	else
		os << "+ " << var.GetCoefficient() << " * X^" << var.GetDegree();
	return os;
}
