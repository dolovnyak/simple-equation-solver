#include <gtest/gtest.h>
#include "SES_SolverData.hpp"

class SES_SolverData_Add_Sub_Expression_Tests : public ::testing::Test {
};

TEST_F(SES_SolverData_Add_Sub_Expression_Tests, Correct_Add_Sub_Degree_0) {
	SES_SolverData solverData;

	solverData.AddExpression(SES_Variable(2.5, 0));
	ASSERT_TRUE(solverData.GetVariables()[0].GetCoefficient() == 2.5);
	ASSERT_TRUE(solverData.GetVariables()[0].GetDegree() == 0);
	solverData.SubExpression(SES_Variable(3.25, 0));
	ASSERT_TRUE(solverData.GetVariables()[0].GetCoefficient() == -0.75);
	ASSERT_TRUE(solverData.GetVariables()[0].GetDegree() == 0);
	solverData.AddExpression(SES_Variable(0.75, 0));
	ASSERT_TRUE(solverData.GetVariables().empty());
	solverData.SubExpression(SES_Variable(1, 0));
	ASSERT_TRUE(solverData.GetVariables()[0].GetCoefficient() == -1);
	ASSERT_TRUE(solverData.GetVariables()[0].GetDegree() == 0);
}

TEST_F(SES_SolverData_Add_Sub_Expression_Tests, Correct_Add_Sub_Degree_1) {
	SES_SolverData solverData;

	solverData.AddExpression(SES_Variable(2.5, 1));
	ASSERT_TRUE(solverData.GetVariables()[0].GetCoefficient() == 2.5);
	ASSERT_TRUE(solverData.GetVariables()[0].GetDegree() == 1);
	solverData.AddExpression(SES_Variable(-3.25, 1));
	ASSERT_TRUE(solverData.GetVariables()[0].GetCoefficient() == -0.75);
	ASSERT_TRUE(solverData.GetVariables()[0].GetDegree() == 1);
	solverData.AddExpression(SES_Variable(0.75, 1));
	ASSERT_TRUE(solverData.GetVariables().empty());
	solverData.SubExpression(SES_Variable(1, 1));
	ASSERT_TRUE(solverData.GetVariables()[0].GetCoefficient() == -1);
	ASSERT_TRUE(solverData.GetVariables()[0].GetDegree() == 1);
}

TEST_F(SES_SolverData_Add_Sub_Expression_Tests, Correct_Add_Sub_Degree_2) {
	SES_SolverData solverData;

	solverData.AddExpression(SES_Variable(2.5, 2));
	ASSERT_TRUE(solverData.GetVariables()[0].GetCoefficient() == 2.5);
	ASSERT_TRUE(solverData.GetVariables()[0].GetDegree() == 2);
	solverData.AddExpression(SES_Variable(-3.25, 2));
	ASSERT_TRUE(solverData.GetVariables()[0].GetCoefficient() == -0.75);
	ASSERT_TRUE(solverData.GetVariables()[0].GetDegree() == 2);
	solverData.AddExpression(SES_Variable(0.75, 2));
	ASSERT_TRUE(solverData.GetVariables().empty());
	solverData.SubExpression(SES_Variable(1, 2));
	ASSERT_TRUE(solverData.GetVariables()[0].GetCoefficient() == -1);
	ASSERT_TRUE(solverData.GetVariables()[0].GetDegree() == 2);
}

TEST_F(SES_SolverData_Add_Sub_Expression_Tests, MultiplyExpressions) {
	SES_SolverData solverData;

	solverData.AddExpression(SES_Variable(24, 2));
	ASSERT_TRUE(solverData.GetVariables()[0].GetCoefficient() == 24);
	ASSERT_TRUE(solverData.GetVariables()[0].GetDegree() == 2);

	solverData.AddExpression(SES_Variable(24, 1));
	ASSERT_TRUE(solverData.GetVariables()[1].GetCoefficient() == 24);
	ASSERT_TRUE(solverData.GetVariables()[1].GetDegree() == 1);

	solverData.AddExpression(SES_Variable(24, 0));
	ASSERT_TRUE(solverData.GetVariables()[2].GetCoefficient() == 24);
	ASSERT_TRUE(solverData.GetVariables()[2].GetDegree() == 0);

	ASSERT_TRUE(solverData.GetVariables().size() == 3);

	solverData.AddExpression(SES_Variable(-24, 2));
	ASSERT_TRUE(solverData.GetVariables().size() == 2);

	solverData.SubExpression(SES_Variable(24, 1));
	ASSERT_TRUE(solverData.GetVariables().size() == 1);

	solverData.AddExpression(SES_Variable(-24, 0));
	ASSERT_TRUE(solverData.GetVariables().empty());

	solverData.AddExpression(SES_Variable(-24, 2));
	solverData.SubExpression(SES_Variable(-15, 2));
	solverData.AddExpression(SES_Variable(-24, 1));
	solverData.AddExpression(SES_Variable(-20, 1));
	solverData.SubExpression(SES_Variable(-24, 0));
	solverData.SubExpression(SES_Variable(-254, 0));
	ASSERT_TRUE(solverData.GetVariables().size() == 3);
}