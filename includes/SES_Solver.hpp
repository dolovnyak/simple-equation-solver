#pragma once

#include "SES_SolverData.hpp"
#include "SES_Answer.hpp"

class SES_Solver {
public:
	static std::shared_ptr<SES_SolverData> Parse(char* str);
//	static SES_Answer
};