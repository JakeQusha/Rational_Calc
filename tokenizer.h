#pragma once
#include <vector>
#include "RationalNumber.h"
namespace tokenizer {
    enum class TokenType{
        ADD_OP,
        SUB_OP,
        MUL_OP,
        DIV_OP,
        RATIONAL,
        LEFT_PAREN,
        RIGHT_PAREN
    };
    struct Token {
        TokenType type;
        RationalNumber value;
        explicit Token(const TokenType& type);
        explicit Token (const RationalNumber& value);
    };
    auto parse_string(const std::string& str)->std::vector<Token>;
}
