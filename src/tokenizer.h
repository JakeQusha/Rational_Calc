#pragma once

#include <vector>
#include <expected>
#include "RationalNumber.h"

namespace tokenizer {
    enum class TokenType {
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
        int pos;

        explicit Token(const TokenType &type, int pos);

        explicit Token(const RationalNumber &value);
    };

    auto parse_string(const std::string &str) -> std::expected<std::vector<Token>, int>;
}
