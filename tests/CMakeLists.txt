target_sources(GTests PUBLIC
        SES_SolverData_Add_Sub_Expression_Tests.cpp
        SES_Variable_Mult_Div_Constructor_Tests.cpp
        Common_Parse_Simplify_Tests.cpp
        Custom_Sqrt_Tests.cpp
        )

target_link_libraries(GTests gtest gtest_main)

enable_testing()
add_test(GTests GTests)