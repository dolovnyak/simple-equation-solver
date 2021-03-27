#include <gtest/gtest.h>
#include <utilities.hpp>
#include "SES_Solver.hpp"

class Common_Parse_Simplify_Tests : public ::testing::Test {
};

TEST_F(Common_Parse_Simplify_Tests, All_Parameters_Reduced) {
	std::shared_ptr<SES_SolverData> solverData;

	char equation[100] = "2 = 2";
	solverData = SES_Solver::Parse(equation);
	ASSERT_TRUE(solverData->GetVariables().empty());
	bzero(equation, 100);

	strcpy(equation, "-2 = 2");
	solverData = SES_Solver::Parse(equation);
	ASSERT_TRUE(solverData->GetVariables()[0].GetCoefficient() == -4);
	ASSERT_TRUE(solverData->GetVariables()[0].GetDegree() == 0);
	bzero(equation, 100);

	strcpy(equation, "-2 = -2");
	solverData = SES_Solver::Parse(equation);
	ASSERT_TRUE(solverData->GetVariables().empty());
	bzero(equation, 100);

	strcpy(equation, "-2 = -2");
	solverData = SES_Solver::Parse(equation);
	ASSERT_TRUE(solverData->GetVariables().empty());
	bzero(equation, 100);

	strcpy(equation, "10x^9 * x^10 / X^31 - -2 * 3X^2 * X^3 / X^8 * X = 10 * x^9 * x^10 / X^31 - -2 * 3 * X^2 * X^3 / X^8 * X");
	solverData = SES_Solver::Parse(equation);
	ASSERT_TRUE(solverData->GetVariables().empty());
	bzero(equation, 100);

	strcpy(equation, "x^11 * X^10 / X^20 * 3 = 3 * x");
	solverData = SES_Solver::Parse(equation);
	ASSERT_TRUE(solverData->GetVariables().empty());
	bzero(equation, 100);
}

TEST_F(Common_Parse_Simplify_Tests, Correct_Simplify) {
	std::shared_ptr<SES_SolverData> solverData;

	char equation[100] = "x^11 * X^10 / X^20 * 3 = 8x - 24 + 14 - -24x^2";
	solverData = SES_Solver::Parse(equation);
	ASSERT_TRUE(solverData->GetVariables()[0].GetCoefficient() == -5);
	ASSERT_TRUE(solverData->GetVariables()[0].GetDegree() == 1);
	ASSERT_TRUE(solverData->GetVariables()[1].GetCoefficient() == 10);
	ASSERT_TRUE(solverData->GetVariables()[1].GetDegree() == 0);
	ASSERT_TRUE(solverData->GetVariables()[2].GetCoefficient() == -24);
	ASSERT_TRUE(solverData->GetVariables()[2].GetDegree() == 2);
	bzero(equation, 100);
}

TEST_F(Common_Parse_Simplify_Tests, Not_Correct_Input) {
	std::shared_ptr<SES_SolverData> solverData;

	char equation[100] = "x^11 * X^10 = 2";
	try {
		solverData = SES_Solver::Parse(equation);
		solverData->CheckCorrect();
		ASSERT_TRUE(false);
	}
	catch (const std::exception& exception) {
		ASSERT_TRUE(contains(exception.what(), "Degree is incorrect in expression: \"1 * X^21\""));
	}
	bzero(equation, 100);

	strcpy(equation, "x^10 / X^11 = 2");
	try {
		solverData = SES_Solver::Parse(equation);
		solverData->CheckCorrect();
		ASSERT_TRUE(false);
	}
	catch (const std::exception& exception) {
		ASSERT_TRUE(contains(exception.what(), "Degree is incorrect in expression: \"1 * X^-1\""));
	}
	bzero(equation, 100);

	strcpy(equation, "x^-1 * x^3 *x = 2");
	try {
		solverData = SES_Solver::Parse(equation);
		solverData->CheckCorrect();
		ASSERT_TRUE(false);
	}
	catch (const std::exception& exception) {
		ASSERT_TRUE(contains(exception.what(), "Degree is incorrect in expression: \"1 * X^3\""));
	}
	bzero(equation, 100);
}
