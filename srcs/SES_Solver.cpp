#include "SES_Solver.hpp"

int yyparse(std::shared_ptr<SES_SolverData> equationSolverData);
extern FILE *yyin;

std::shared_ptr<SES_SolverData> SES_Solver::Parse(char *str) {
	FILE *file = fmemopen(str, strlen(str), "r");

	yyin = file;
	std::shared_ptr<SES_SolverData> equationSolverData(new SES_SolverData);
	yyparse(equationSolverData);
	fclose(file);

	return equationSolverData;
}

SES_Solution SES_Solver::Solve(const std::shared_ptr<SES_SolverData>& solverData) {
	SES_Solution solution;

	if (solverData->GetMaxDegree() == 0) {
		solution.AddSolutionString("Each real number.");
	}
	else {
		;
	}

	return solution;
}
