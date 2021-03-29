#include "SES_Solver.hpp"

int main(int argc, char **argv) {
	std::string stringEquation;

	if (argc == 2) {
		stringEquation = argv[1];
	}
	else if (argc == 1) {
		std::getline(std::cin, stringEquation);
	}
	else {
		std::cout << "Arguments number is incorrect." << std::endl;
		exit(0);
	}

	try {
		std::shared_ptr<SES_SolverData> solverData = SES_Solver::Parse(stringEquation.c_str());
		std::cout << "Reduced form: " << *solverData << std::endl;
		std::cout << "Polynomial degree: " << solverData->GetMaxDegree() << std::endl;

		if (!solverData->IsDegreeCorrect()) {
			std::cout << "The polynomial degree should be strictly >= 0 and <= 2, it will not be solved." << std::endl;
			exit(0);
		}
		SES_Solution solution = SES_Solver::Solve(solverData);
		std::cout << solution;
	}
	catch (const std::exception &exception) {
		std::cout << exception.what() << std::endl;
	}

	exit(0);
}