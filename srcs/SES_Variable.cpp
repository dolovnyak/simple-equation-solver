#include "SES_Variable.hpp"

SES_Variable::SES_Variable(double coefficient, int degree) : _coefficient(coefficient), _degree(degree) {
	if (!IsDegreeCorrect(degree))
		throw NotCorrectDegreeException(this->ToString());
}

SES_Variable SES_Variable::operator*(const SES_Variable& var) const {
	if (!IsDegreeCorrect(_degree + var._degree)) {
		throw NotCorrectDegreeException(this->ToString() + " * " + var.ToString(), _degree - var._degree);
	}
	SES_Variable newVar(_coefficient * var._coefficient, _degree + var._degree);
	return newVar;
}

SES_Variable SES_Variable::operator/(const SES_Variable& var) const {
	if (!IsDegreeCorrect(_degree - var._degree)) {
		throw NotCorrectDegreeException(this->ToString() + " / " + var.ToString(), _degree - var._degree);
	}
	SES_Variable newVar(_coefficient / var._coefficient, _degree - var._degree);
	return newVar;
}

bool SES_Variable::IsDegreeCorrect(int degree) {
	if (degree >= 0 && degree <= 2)
		return true;
	return false;
}

double SES_Variable::GetCoefficient() const {
	return _coefficient;
}

int SES_Variable::GetDegree() const {
	return _degree;
}

std::string SES_Variable::ToString() const {
	std::ostringstream correctConvertingStream;
	correctConvertingStream << _coefficient;

	return correctConvertingStream.str() + " * X^" + std::to_string(_degree);
}

std::ostream &operator<<(std::ostream &os, const SES_Variable& var) {
	if (var.GetCoefficient() < 0)
		os << "- " << var.GetCoefficient() * -1 << " * X^" << var.GetDegree();
	else
		os << "+ " << var.GetCoefficient() << " * X^" << var.GetDegree();
	return os;
}

const char *SES_Variable::NotCorrectDegreeException::what() const noexcept {
	return exception_.c_str();
}

SES_Variable::NotCorrectDegreeException::NotCorrectDegreeException(const std::string& stringVar) {
	exception_ = "Degree is incorrect in expression: \"" + stringVar + "\"";
}

SES_Variable::NotCorrectDegreeException::NotCorrectDegreeException(
		const std::string& stringOperationVars, int finalResultDegree) {
	exception_ = "Degree is incorrect in expression: \"" + stringOperationVars +
			"\", final result degree: " + std::to_string(finalResultDegree);
}
