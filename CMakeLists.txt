cmake_minimum_required(VERSION 3.27)
project(Rational_Calc)

set(CMAKE_CXX_STANDARD 23)

add_executable(Rational_Calc src/main.cpp
        src/RationalNumber.cpp
        src/RationalNumber.h
        src/tokenizer.cpp
        src/tokenizer.h
        src/calc.cpp
        src/calc.h)
