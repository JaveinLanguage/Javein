cmake_minimum_required(VERSION 3.10)

project(Javein)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Javein
        src/main.cpp
        src/lexer.cpp
        src/parser.cpp
        src/parser/parser_conditions.cpp
        src/parser/parser_loops.cpp
        src/parser/parser_functions.cpp
        src/parser/parser_classes.cpp
        src/parser/parser_variables.cpp
        src/parser/parser_constructors.cpp

        include/lexer.hpp
        include/parser.hpp
        include/parser/parser_conditions.hpp
        include/parser/parser_loops.hpp
        include/parser/parser_functions.hpp
        include/parser/parser_classes.hpp
        include/parser/parser_variables.hpp
        include/parser/parser_constructors.hpp
        include/errors.hpp)

target_include_directories(Javein PRIVATE include)