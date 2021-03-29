#include <gtest/gtest.h>
#include <SES_Solver.hpp>

class Subject_Checklist_Tests : public ::testing::Test {};

TEST_F(Subject_Checklist_Tests, Subject_Tests) {
	std::string equation = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
	std::shared_ptr<SES_SolverData> solverData = SES_Solver::Parse(equation.c_str());
	ASSERT_TRUE(contains(solverData->ToString(), "4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0"));
	ASSERT_TRUE(solverData->GetMaxDegree() == 2);
	SES_Solution solution = SES_Solver::Solve(solverData);
	ASSERT_TRUE(contains(solution.ToString(), "there are two solutions:"));
	ASSERT_TRUE(contains(solution.ToString(), "0.905239"));
	ASSERT_TRUE(contains(solution.ToString(), "-0.475131"));

	equation = "5 * X^0 + 4 * X^1 = 4 * X^0";
	solverData = SES_Solver::Parse(equation.c_str());
	ASSERT_TRUE(contains(solverData->ToString(), "1 * X^0 + 4 * X^1 = 0"));
	ASSERT_TRUE(solverData->GetMaxDegree() == 1);
	solution = SES_Solver::Solve(solverData);
	ASSERT_TRUE(contains(solution.ToString(), "The solution is:"));
	ASSERT_TRUE(contains(solution.ToString(), "-0.25"));

	equation = "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0";
	solverData = SES_Solver::Parse(equation.c_str());
	ASSERT_TRUE(contains(solverData->ToString(), "5 * X^0 - 6 * X^1 - 5.6 * X^3 = 0"));
	ASSERT_TRUE(solverData->GetMaxDegree() == 3);
	ASSERT_TRUE(!solverData->IsDegreeCorrect());

	equation = "5 + 4 * X + X^2= X^2";
	solverData = SES_Solver::Parse(equation.c_str());
	ASSERT_TRUE(contains(solverData->ToString(), "5 * X^0 + 4 * X^1 = 0"));
	ASSERT_TRUE(solverData->GetMaxDegree() == 1);
	solution = SES_Solver::Solve(solverData);
	ASSERT_TRUE(contains(solution.ToString(), "The solution is:"));
	ASSERT_TRUE(contains(solution.ToString(), "-1.25"));
}

TEST_F(Subject_Checklist_Tests, Checklist_Tests) {
	std::string equation = "5 * x^0 = 5 * x^0";
	std::shared_ptr<SES_SolverData> solverData = SES_Solver::Parse(equation.c_str());
	ASSERT_TRUE(contains(solverData->ToString(), "0 = 0"));
	SES_Solution solution = SES_Solver::Solve(solverData);
	ASSERT_TRUE(contains(solution.ToString(), "The solution is:"));
	ASSERT_TRUE(contains(solution.ToString(), "Each real number."));

	equation = "4 * X^0 = 8 * x^0";
	solverData = SES_Solver::Parse(equation.c_str());
	ASSERT_TRUE(contains(solverData->ToString(), "-4 * X^0 = 0"));
	solution = SES_Solver::Solve(solverData);
	ASSERT_TRUE(contains(solution.ToString(), "Equation is incorrect, there is no solution."));

	equation = "5 = 4 + 7x";
	solverData = SES_Solver::Parse(equation.c_str());
	ASSERT_TRUE(contains(solverData->ToString(), "1 * X^0 - 7 * X^1 = 0"));
	solution = SES_Solver::Solve(solverData);
	ASSERT_TRUE(contains(solution.ToString(), "The solution is:"));
	ASSERT_TRUE(contains(solution.ToString(), "0.142857"));

	equation = "5 + 13x + 3x^2 = 1 + 1x";
	solverData = SES_Solver::Parse(equation.c_str());
	ASSERT_TRUE(contains(solverData->ToString(), "4 * X^0 + 12 * X^1 + 3 * X^2 = 0"));
	solution = SES_Solver::Solve(solverData);
	ASSERT_TRUE(contains(solution.ToString(), "Discriminant = 96"));
	ASSERT_TRUE(contains(solution.ToString(), "there are two solutions"));
	ASSERT_TRUE(contains(solution.ToString(), "-3.63299"));
	ASSERT_TRUE(contains(solution.ToString(), "-0.367007"));

	equation = "6 + 11x + 5x^2 = 1 + x";
	solverData = SES_Solver::Parse(equation.c_str());
	ASSERT_TRUE(contains(solverData->ToString(), "5 * X^0 + 10 * X^1 + 5 * X^2 = 0"));
	solution = SES_Solver::Solve(solverData);
	ASSERT_TRUE(contains(solution.ToString(), "Discriminant = 0"));
	ASSERT_TRUE(contains(solution.ToString(), "there is one solution"));
	ASSERT_TRUE(contains(solution.ToString(), "-1"));

	equation = "5 + 3x + 3x^2 = 1 + 0 * X^1";
	solverData = SES_Solver::Parse(equation.c_str());
	ASSERT_TRUE(contains(solverData->ToString(), "4 * X^0 + 3 * X^1 + 3 * X^2 = 0"));
	solution = SES_Solver::Solve(solverData);
	ASSERT_TRUE(contains(solution.ToString(), "Discriminant = -39, it's strictly negative, there are two complex solutions"));
	ASSERT_TRUE(contains(solution.ToString(), "-0.5 - i * 1.04083"));
	ASSERT_TRUE(contains(solution.ToString(), "-0.5 + i * 1.04083"));

	equation = "3x^3 /x + x^5 = x^5";
	solverData = SES_Solver::Parse(equation.c_str());
	ASSERT_TRUE(contains(solverData->ToString(), "3 * X^2 = 0"));
	solution = SES_Solver::Solve(solverData);
	ASSERT_TRUE(contains(solution.ToString(), "Discriminant = 0, there is one solution"));

	equation = "3x^3 + x^5 = x^5";
	solverData = SES_Solver::Parse(equation.c_str());
	ASSERT_TRUE(contains(solverData->ToString(), "3 * X^3 = 0"));
	ASSERT_TRUE(!solverData->IsDegreeCorrect());
}
