target_sources(${PROJECT_NAME} PUBLIC
        main.cpp
        SES_Solver.cpp
        SES_SolverData.cpp
        SES_Variable.cpp
        utilities.cpp
        )

target_sources(GTests PUBLIC
        SES_Solver.cpp
        SES_SolverData.cpp
        SES_Variable.cpp
        utilities.cpp
        )

add_subdirectory(Parse)
