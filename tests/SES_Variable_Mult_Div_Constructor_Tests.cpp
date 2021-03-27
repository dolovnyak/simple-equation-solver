#include "utilities.hpp"
#include <gtest/gtest.h>
#include "SES_Variable.hpp"

class SES_Variable_Mult_Div_Constructor_Tests : public ::testing::Test {
};

TEST_F(SES_Variable_Mult_Div_Constructor_Tests, SES_Var_Constructor_Test) {
	try {
		SES_Variable var0(2, 0);
		ASSERT_TRUE(var0.GetDegree() == 0);
		ASSERT_TRUE(var0.GetCoefficient() == 2);

		SES_Variable var1(512.53, 1);
		ASSERT_TRUE(var1.GetDegree() == 1);
		ASSERT_TRUE(var1.GetCoefficient() == 512.53);

		SES_Variable var2(51.2, 2);
		ASSERT_TRUE(var2.GetDegree() == 2);
		ASSERT_TRUE(var2.GetCoefficient() == 51.2);
	}
	catch (const std::exception& exception) {
		std::cout << exception.what() << std::endl;
		ASSERT_TRUE(false);
	}

	try {
		SES_Variable var3(14, -1);
		ASSERT_TRUE(false);
	}
	catch (const std::exception& exception) {
		ASSERT_TRUE(contains(exception.what(), "Degree is incorrect in expression: \"14 * X^-1\""));
	}

	try {
		SES_Variable var4(14, 3);
		ASSERT_TRUE(false);
	}
	catch (const std::exception& exception) {
		ASSERT_TRUE(contains(exception.what(), "Degree is incorrect in expression: \"14 * X^3\""));
	}

	try{
	SES_Variable varMult1(2, 2);
	varMult1 = varMult1 * SES_Variable(-2, 0);
	ASSERT_TRUE(varMult1.GetCoefficient() == -4);
	ASSERT_TRUE(varMult1.GetDegree() == 2);

	varMult1 = varMult1 / SES_Variable(-8, 2);
	ASSERT_TRUE(varMult1.GetCoefficient() == 0.5);
	ASSERT_TRUE(varMult1.GetDegree() == 0);

	varMult1 = varMult1 * SES_Variable(-2, 1);
	ASSERT_TRUE(varMult1.GetCoefficient() == -1);
	ASSERT_TRUE(varMult1.GetDegree() == 1);
	}
	catch (const std::exception& exception) {
		std::cout << exception.what() << std::endl;
		ASSERT_TRUE(false);
	}

	try {
		SES_Variable varMult(14, 2);
		varMult = varMult * SES_Variable(42, 1);
		ASSERT_TRUE(false);
	}
	catch (const std::exception& exception) {
		ASSERT_TRUE(contains(exception.what(), "Degree is incorrect in expression: \"14 * X^2 * 42 * X^1\""));
	}

	try {
		SES_Variable varDiv(14, 1);
		varDiv = varDiv / SES_Variable(42, 2);
		ASSERT_TRUE(false);
	}
	catch (const std::exception& exception) {
		ASSERT_TRUE(contains(exception.what(), "Degree is incorrect in expression: \"14 * X^1 / 42 * X^2\""));
	}
}