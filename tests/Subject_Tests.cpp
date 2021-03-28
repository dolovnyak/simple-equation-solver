#include <gtest/gtest.h>
#include <SES_Solver.hpp>

class Subject_Tests : public ::testing::Test {};

TEST_F(Subject_Tests, Subject_Tests) {
	char input1[100] = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
	std::shared_ptr<SES_SolverData> solverData = SES_Solver::Parse(input1);
	ASSERT_TRUE(contains(solverData->ToString(), "4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0"));
	ASSERT_TRUE(solverData->GetMaxDegree() == 2);
	SES_Solution solution = SES_Solver::Solve(solverData);
	ASSERT_TRUE(contains(solution.ToString(), "there is two solutions:"));
	ASSERT_TRUE(contains(solution.ToString(), "0.905239"));
	ASSERT_TRUE(contains(solution.ToString(), "-0.475131"));

	char input2[100] = "5 * X^0 + 4 * X^1 = 4 * X^0";
	solverData = SES_Solver::Parse(input2);
	ASSERT_TRUE(contains(solverData->ToString(), "1 * X^0 + 4 * X^1 = 0"));
	ASSERT_TRUE(solverData->GetMaxDegree() == 1);
	solution = SES_Solver::Solve(solverData);
	ASSERT_TRUE(contains(solution.ToString(), "The solution is:"));
	ASSERT_TRUE(contains(solution.ToString(), "-0.25"));

	char input3[100] = "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0";
	solverData = SES_Solver::Parse(input3);
	ASSERT_TRUE(contains(solverData->ToString(), "5 * X^0 - 6 * X^1 - 5.6 * X^3 = 0"));
	ASSERT_TRUE(solverData->GetMaxDegree() == 3);
	ASSERT_TRUE(!solverData->IsDegreeCorrect());

	char input4[100] = "5 + 4 * X + X^2= X^2";
	solverData = SES_Solver::Parse(input4);
	ASSERT_TRUE(contains(solverData->ToString(), "5 * X^0 + 4 * X^1 = 0"));
	ASSERT_TRUE(solverData->GetMaxDegree() == 1);
	solution = SES_Solver::Solve(solverData);
	ASSERT_TRUE(contains(solution.ToString(), "The solution is:"));
	ASSERT_TRUE(contains(solution.ToString(), "-1.25"));
}
