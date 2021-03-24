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
		//TODO print something
		exit(0);
	}

	try {
		std::shared_ptr<SES_SolverData> equationSolverData = SES_Solver::Parse(argv[1]);
		SES_Solver::Simplify(equationSolverData);
		std::cout << equationSolverData << std::endl; //TODO SES_SolverData std::cout overload needed
//		SES_Solver::
	}
	catch (const std::exception &exception) {
		std::cout << "Exception: " << exception.what() << std::endl;
	}

	exit(0);
}
