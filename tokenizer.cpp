#include <iostream>
#include "tokenizer.h"

tokenizer::Token::Token(TokenType type) {
    this->type = type;

}

tokenizer::Token::Token(RationalNumber value) {
    this->type = TokenType::RATIONAL;
    this->value = value;
}


auto tokenizer::parse_string(const std::string &str) -> std::vector<Token> {
    std::vector<Token> result;
    for (int i = 0; i < str.size(); ++i) {
        switch (str.at(i)) {
            case '+':
                result.emplace_back(TokenType::ADD_OP);
                break;
            case '-':
                result.emplace_back(TokenType::SUB_OP);
                break;
            case '*':
                result.emplace_back(TokenType::MUL_OP);
                break;
            case '/':
                result.emplace_back(TokenType::DIV_OP);
                break;
            case '(':
                result.emplace_back(TokenType::LEFT_PAREN);
                break;
            case ')':
                result.emplace_back(TokenType::RIGHT_PAREN);
                break;
            case ' ':
                continue;
            default:
                if (!isdigit(str.at(i))) {
                    //error
                    std::cout << "le invalido tokenno";
                    continue;
                }
                int num=0;
                do {
                    num *= 10;
                    num += str.at(i) - '0';
                } while (isdigit(str.at(++i)));
                i--;
                result.emplace_back(RationalNumber(num,1));
                break;
        }
    }
    return result;
}

