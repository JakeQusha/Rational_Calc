#include <ranges>
#include <iostream>
#include <format>
#include "calc.h"

auto calculator::evaluate_equation(std::vector<tokenizer::Token> equation) -> RationalNumber {
    int first_index = -1, depth = 0;
    for (int i = 0; i < equation.size(); ++i) {

        if (equation.at(i).type == tokenizer::TokenType::LEFT_PAREN) {
            if (first_index == -1) {
                first_index = i;
            }
            depth++;
        } else if (equation.at(i).type == tokenizer::TokenType::RIGHT_PAREN) {
            depth--;
            if (first_index != -1 && depth == 0) {
                RationalNumber repl = evaluate_equation({equation.begin() + first_index + 1, equation.begin() + i});
                equation.erase(equation.begin() + first_index, equation.begin() + i + 1);
                equation.insert(equation.begin() + first_index, tokenizer::Token(repl));
                i = first_index;
                first_index = -1;
            }
        }
        if (depth < 0) {
            std::cout << "invalifa";
            return {};
        }
    }
    if (depth > 0) {
        std::cout << "invalifa";
        return {};
    }
    if(!equation.size()){
        return {};
    }

    switch (equation.front().type) {
        case tokenizer::TokenType::ADD_OP:
            equation.erase(equation.begin());
            break;
        case tokenizer::TokenType::SUB_OP:
            equation.front().value = -equation.front().value;
            equation.erase(equation.begin());
            break;
        case tokenizer::TokenType::RATIONAL:
            break;
        default:
            std::cout << "invalifa";
    }
    for (int i = 0; i < equation.size() - 1; ++i) {
        switch (equation.at(i).type) {
            case tokenizer::TokenType::ADD_OP:
                switch (equation.at(i + 1).type) {
                    case tokenizer::TokenType::SUB_OP:
                        equation.erase(equation.begin() + i);
                        break;
                    case tokenizer::TokenType::RATIONAL:
                        break;
                    default:
                        std::cout << "invalifa";
                        break;
                }
                break;
            case tokenizer::TokenType::SUB_OP:
                switch (equation.at(i + 1).type) {
                    case tokenizer::TokenType::ADD_OP:
                        equation.erase(equation.begin() + 1 + i);
                        break;
                    case tokenizer::TokenType::SUB_OP:
                        equation.at(i).type = tokenizer::TokenType::ADD_OP;
                        equation.erase(equation.begin() + 1 + i);
                        break;
                    case tokenizer::TokenType::RATIONAL:
                        break;
                    default:
                        std::cout << "invalifa";
                        break;
                }
                break;
            case tokenizer::TokenType::MUL_OP:
                switch (equation.at(i + 1).type) {
                    case tokenizer::TokenType::ADD_OP:
                        equation.erase(equation.begin() + 1 + i);
                        break;
                    case tokenizer::TokenType::SUB_OP:
                        if (equation.size() > i + 2 && equation.at(i + 2).type == tokenizer::TokenType::RATIONAL) {
                            equation.at(i + 2).value = -equation.at(i + 2).value;
                            equation.erase(equation.begin() + 1 + i);
                        } else {
                            std::cout << "invalifa";
                        }
                        break;
                    case tokenizer::TokenType::RATIONAL:
                        break;
                    default:
                        std::cout << "invalifa";
                        break;
                }
                break;
            case tokenizer::TokenType::DIV_OP:
                switch (equation.at(i + 1).type) {
                    case tokenizer::TokenType::ADD_OP:
                        equation.erase(equation.begin() + 1 + i);
                        break;
                    case tokenizer::TokenType::SUB_OP:
                        if (equation.size() > i + 2 && equation.at(i + 2).type == tokenizer::TokenType::RATIONAL) {
                            equation.at(i + 2).value = -equation.at(i + 2).value;
                            equation.erase(equation.begin() + 1 + i);
                        } else {
                            std::cout << "invalifa";
                        }
                        break;
                    case tokenizer::TokenType::RATIONAL:
                        break;
                    default:
                        std::cout << "invalifa";
                        break;
                }
                break;
            case tokenizer::TokenType::RATIONAL:
                if (equation.at(i + 1).type == tokenizer::TokenType::LEFT_PAREN ||
                    equation.at(i + 1).type == tokenizer::TokenType::RIGHT_PAREN) { std::cout << "invalifa"; }
                if (equation.at(i + 1).type == tokenizer::TokenType::RATIONAL) {
                    equation.insert(equation.begin() + i, tokenizer::Token(tokenizer::TokenType::MUL_OP));
                    i++;
                }
                break;
            default:
                std::cout << "invalifa";
                break;
        }
    }
    if(equation.back().type != tokenizer::TokenType::RATIONAL){
        std::cout << "invalifa";}
    for (int i = 0; i < ((int)equation.size())-2;) {
        switch (equation.at(i+1).type) {
            case tokenizer::TokenType::ADD_OP:
                equation.at(i).value = equation.at(i+2).value + equation.at(i).value;
                break;
            case tokenizer::TokenType::SUB_OP:
                equation.at(i).value = equation.at(i+2).value - equation.at(i).value;
                break;
            case tokenizer::TokenType::MUL_OP:
                equation.at(i).value = equation.at(i+2).value * equation.at(i).value;
                break;
            case tokenizer::TokenType::DIV_OP:
                equation.at(i).value = equation.at(i+2).value / equation.at(i).value;
                break;
            default:
                std::cout << "invalifa";
        }
        equation.erase(equation.begin()+i+1,equation.begin()+i+3);
    }
    return equation.at(0).value;
}

auto calculator::evaluate_string(const std::string &str) -> RationalNumber {
    return evaluate_equation(tokenizer::parse_string(str));
}