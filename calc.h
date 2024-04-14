#pragma once
#include <vector>
#include "RationalNumber.h"
#include "tokenizer.h"

namespace calculator{
    auto evaluate_equation(std::vector<tokenizer::Token> equation) -> RationalNumber;
    auto evaluate_string(const std::string& str) -> RationalNumber;
}
