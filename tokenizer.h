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
    class Token {
        TokenType type;
        RationalNumber value;
    public:
        explicit Token(TokenType type);
        explicit Token (RationalNumber value);
    };
    auto parse_string(const std::string& str)->std::vector<Token>;
}