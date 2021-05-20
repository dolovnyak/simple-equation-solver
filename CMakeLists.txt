cmake_minimum_required(VERSION 3.15)
project(simple-equation-solver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_STANDARD 17)

################################################################################
# simple-equation-solver lib target
################################################################################
set(EQUATION_SOLVER_LIB "${PROJECT_NAME}-lib")
add_library(${EQUATION_SOLVER_LIB}
        srcs/SolverLib/SES_Solver.cpp
        srcs/SolverLib/SES_SolverData.cpp
        srcs/SolverLib/SES_Variable.cpp
        srcs/SolverLib/SES_Solution.cpp
        srcs/SolverLib/utilities.cpp
        srcs/SolverLib/Parse/Grammar.yy.cpp
        srcs/SolverLib/Parse/Lexer.ll.cpp
        )
include(ParseGenerator.cmake)
target_include_directories(${EQUATION_SOLVER_LIB} PUBLIC includes)

################################################################################
# project target
################################################################################
add_executable(${PROJECT_NAME}
        srcs/main.cpp
        )
target_link_libraries(${PROJECT_NAME} ${EQUATION_SOLVER_LIB})
target_include_directories(${PROJECT_NAME} PUBLIC includes)

# replaced executable file to root dir
set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )

################################################################################
# tests
################################################################################
set(EQUATION_SOLVER_TESTS ${PROJECT_NAME}-tests)
add_subdirectory(libs/googletest)

add_executable(${EQUATION_SOLVER_TESTS}
        tests/Common_Parse_Simplify_Tests.cpp
        tests/Custom_Sqrt_Tests.cpp
        tests/SES_SolverData_Add_Sub_Expression_Tests.cpp
        tests/SES_Variable_Mult_Div_Constructor_Tests.cpp
        tests/Subject_Checklist_Tests.cpp
        )
target_include_directories(${EQUATION_SOLVER_TESTS} PUBLIC
        libs/googletest/googletest/include
        includes)
target_link_libraries(${EQUATION_SOLVER_TESTS}
        gtest
        gtest_main
        ${EQUATION_SOLVER_LIB}
        )

# replaced executable file to root dir
set_target_properties(${EQUATION_SOLVER_TESTS}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )
