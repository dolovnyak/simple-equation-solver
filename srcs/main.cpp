#include "SES_Solver.hpp"

bool isInputCorrect(int argc)
{
	if (argc != 2)
		return false;
	return true;
}

int main(int argc, char **argv)
{
	if (!isInputCorrect(argc)) {
		std::cout << "Only one string expected in argument." << std::endl;
		exit(0);
	}

	try {
		std::shared_ptr<SES_SolverData> solverData = SES_Solver::Parse(argv[1]);
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