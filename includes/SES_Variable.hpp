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
	[[nodiscard]] bool IsCorrect() const;

private:
	double _coefficient;
	int _degree;
};

std::ostream &operator<<(std::ostream &os, const SES_Variable& var);