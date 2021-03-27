target_sources(${PROJECT_NAME} PUBLIC
        Grammar.yy.cpp
        Lexer.ll.cpp
        )

target_sources(GTests PUBLIC
        Grammar.yy.cpp
        Lexer.ll.cpp
        )

INCLUDE(ParseGenerator.cmake)