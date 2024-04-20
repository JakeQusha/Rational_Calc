cmake_minimum_required(VERSION 3.27)
project(Rational_Calc)

set(CMAKE_CXX_STANDARD 23)

add_executable(Rational_Calc main.cpp
        RationalNumber.cpp
        RationalNumber.h
        tokenizer.cpp
        tokenizer.h
        calc.cpp
        calc.h)
