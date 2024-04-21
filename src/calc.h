#pragma once

#include <vector>
#include "RationalNumber.h"
#include "tokenizer.h"

namespace calculator {
    enum class ErrorType {
        INVALID_STRING,
        UNEXPECTED_RIGHT_PAREN,
        MISSING_RIGHT_PAREN,
        UNEXPECTED_TOKEN,
        MISSING_END,
        ZERO_DIVISION,
        LOGIC_ERROR
    };

    struct Error {
        ErrorType type;
        int where;

        Error() = delete;

        Error(ErrorType type, int where);
    };

    auto evaluate_equation(std::vector<tokenizer::Token> equation) -> std::expected<RationalNumber, Error>;

    auto evaluate_string(const std::string &str) -> std::expected<RationalNumber, Error>;
}
