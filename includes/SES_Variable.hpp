#pragma once

#include <iostream>
#include <sstream>

struct SES_Variable {
public:
	explicit SES_Variable(double coefficient, int degree);

	[[nodiscard]] SES_Variable operator*(const SES_Variable& var) const;
	[[nodiscard]] SES_Variable operator/(const SES_Variable& var) const;
	[[nodiscard]] double GetCoefficient() const;
	[[nodiscard]] int GetDegree() const;
	[[nodiscard]] std::string ToString() const;

private:
	double _coefficient;
	int _degree;

	[[nodiscard]] static bool IsDegreeCorrect(int degree) ;

	class NotCorrectDegreeException : public std::exception {
	public:
		explicit NotCorrectDegreeException(const std::string& stringVar);
		explicit NotCorrectDegreeException(const std::string& stringOperationVars, int finalResultDegree);
		[[nodiscard]] const char *what() const _NOEXCEPT override;

	private:
		std::string exception_;
	};
};

std::ostream &operator<<(std::ostream &os, const SES_Variable& var);