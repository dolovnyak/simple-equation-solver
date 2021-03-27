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
		std::cout << "only one string expected in argument" << std::endl;
		exit(0);
	}

	try {
		std::shared_ptr<SES_SolverData> solverData = SES_Solver::Parse(argv[1]);
		solverData->CheckCorrect();
		std::cout << *solverData << std::endl;

//		SES_Solver::Solve
	}
	catch (const std::exception &exception) {
		std::cout << "Exception: " << exception.what() << std::endl;
	}

	exit(0);
}