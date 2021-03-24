#pragma once

#include "SES_SolverData.hpp"
#include "SES_Answer.hpp"

class SES_Solver {
public:
	static std::shared_ptr<SES_SolverData> Parse(char* str);
	static void Simplify(std::shared_ptr<SES_SolverData> equationSolverData);
//	static SES_Answer
};