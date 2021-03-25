#include "SES_Solver.hpp"

int yyparse(std::shared_ptr<SES_SolverData> equationSolverData);
extern FILE *yyin;

std::shared_ptr<SES_SolverData> SES_Solver::Parse(char *str) {
	FILE *file = fmemopen(str, strlen(str), "r");

	yyin = file;
	std::shared_ptr<SES_SolverData> equationSolverData(new SES_SolverData);
	yyparse(equationSolverData);
	fclose(file);

	std::cout << *equationSolverData << std::endl;
	return equationSolverData;
}