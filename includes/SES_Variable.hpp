#pragma once

#include <iostream>

struct SES_Variable {
public:
	SES_Variable(double coefficient, int degree);

	SES_Variable operator*(const SES_Variable& var) const;
	double GetCoefficient() const;
	int GetDegree() const;

private:
	double _coefficient;
	int _degree;

	bool isCorrect();
};

std::ostream &operator<<(std::ostream &os, const SES_Variable& var);