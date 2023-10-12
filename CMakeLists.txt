cmake_minimum_required(VERSION 3.10)

# Définir le nom du projet
project(Javein)

# Spécifier la version de C++ à utiliser
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Javein src/main.cpp src/lexer.cpp include/lexer.h include/parser.h src/parser.cpp)