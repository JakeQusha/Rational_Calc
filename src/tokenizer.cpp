#include <iostream>
#include "tokenizer.h"

tokenizer::Token::Token(const TokenType &type, int pos) : value(0, 1), type(type), pos(pos) {}

tokenizer::Token::Token(const RationalNumber &value) : value(value), type(TokenType::RATIONAL), pos(0) {}

auto tokenizer::parse_string(const std::string &str) -> std::expected<std::vector<Token>, int> {
    std::vector<Token> result;
    for (int i = 0; i < str.size(); ++i) {
        switch (str.at(i)) {
            case '+':
                result.emplace_back(TokenType::ADD_OP, i);
                break;
            case '-':
                result.emplace_back(TokenType::SUB_OP, i);
                break;
            case '*':
                result.emplace_back(TokenType::MUL_OP, i);
                break;
            case '/':
                result.emplace_back(TokenType::DIV_OP, i);
                break;
            case '(':
                result.emplace_back(TokenType::LEFT_PAREN, i);
                break;
            case ')':
                result.emplace_back(TokenType::RIGHT_PAREN, i);
                break;
            case ' ':
                continue;
            default:
                if (!isdigit(str.at(i))) {
                    //error
                    return std::unexpected(i);
                }
                int num = 0;
                do {
                    num *= 10;
                    num += str.at(i) - '0';
                    if (str.size() <= i + 1) {
                        i++;
                        break;
                    }
                } while (isdigit(str.at(++i)));
                i--;
                result.emplace_back(RationalNumber(num, 1));
                break;
        }
    }
    return result;
}

