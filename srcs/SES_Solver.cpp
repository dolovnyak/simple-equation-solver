#include "SES_Solver.hpp"

int yyparse(std::shared_ptr<SES_SolverData> equationSolverData);
extern FILE *yyin;

std::shared_ptr<SES_SolverData> SES_Solver::Parse(const char *str) {
	FILE *file = fmemopen((void*)str, strlen(str), "r");

	yyin = file;
	std::shared_ptr<SES_SolverData> equationSolverData(new SES_SolverData);
	yyparse(equationSolverData);
	fclose(file);

	return equationSolverData;
}

SES_Solution SES_Solver::Solve(const std::shared_ptr<SES_SolverData>& solverData) {
	SES_Solution solution;
	std::ostringstream correctConvertingStream;

	if (solverData->GetVariables().empty()) {
		solution.AddSolutionString("The solution is:");
		solution.AddSolutionString("Each real number.");
	}
	else if (solverData->GetMaxDegree() == 0) {
		solution.AddSolutionString("Equation is incorrect, there is no solution.");
	}
	else if (solverData->GetMaxDegree() == 1) {
		correctConvertingStream << "The solution is:" << std::endl <<
			(-solverData->GetCoefficientByDegree(0) / solverData->GetCoefficientByDegree(1));
		solution.AddSolutionString(correctConvertingStream.str());
	}
	else if (solverData->GetMaxDegree() == 2) {
		double a = solverData->GetCoefficientByDegree(2);
		double b = solverData->GetCoefficientByDegree(1);
		double c = solverData->GetCoefficientByDegree(0);
		double discriminant = b * b - 4.0 * a * c;
		discriminant = n_zero_avoid(discriminant);

		if (discriminant < 0) {
			correctConvertingStream << "Discriminant = " << discriminant << ", it's strictly negative, there are two complex solutions:" << std::endl;
			double ax = n_zero_avoid(-b / (2.0 * a));
			double bi = n_zero_avoid(custom_sqrt(-discriminant) / (2.0 * a));
			correctConvertingStream << ax << " - i * " << bi << std::endl;
			correctConvertingStream << ax << " + i * " << bi << std::endl;
			solution.AddSolutionString(correctConvertingStream.str());
		}
		else if (discriminant == 0) {
			correctConvertingStream << "Discriminant = " << discriminant << ", there is one solution:" << std::endl;
			correctConvertingStream << n_zero_avoid(-b / (2.0 * a));
			solution.AddSolutionString(correctConvertingStream.str());
		}
		else {
			correctConvertingStream << "Discriminant = " << discriminant << ", it's strictly positive, there are two solutions:" << std::endl;
			correctConvertingStream << n_zero_avoid((-b - custom_sqrt(discriminant)) / (2.0 * a)) << std::endl;
			correctConvertingStream << n_zero_avoid((-b + custom_sqrt(discriminant)) / (2.0 * a)) << std::endl;
			solution.AddSolutionString(correctConvertingStream.str());
		}
	}
	else {
		solution.AddSolutionString("The polynomial degree should be strictly >= 0 and <= 2, it will not be solved.");
	}

	return solution;
}