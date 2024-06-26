#include <format>
#include <set>
#include "calc.h"

calculator::Error::Error(calculator::ErrorType type, int where) : type(type), where(where) {}

using namespace tokenizer;

auto calculator::evaluate_equation(std::vector<Token> equation) -> std::expected<RationalNumber, Error> {
    int first_index = -1, depth = 0;
    for (int i = 0; i < equation.size(); ++i) {

        if (equation.at(i).type == TokenType::LEFT_PAREN) {
            if (first_index == -1) {
                first_index = i;
            }
            depth++;
        } else if (equation.at(i).type == TokenType::RIGHT_PAREN) {
            depth--;
            if (first_index != -1 && depth == 0) {
                auto repl = evaluate_equation({equation.begin() + first_index + 1, equation.begin() + i});
                if (!repl) {
                    return std::unexpected(repl.error());
                }
                equation.erase(equation.begin() + first_index, equation.begin() + i + 1);
                equation.insert(equation.begin() + first_index, Token(*repl));
                i = first_index;
                first_index = -1;
            }
        }
        if (depth < 0) {
            return std::unexpected(Error(ErrorType::UNEXPECTED_RIGHT_PAREN, equation.at(i).pos));
        }
    }
    if (depth > 0) {
        return std::unexpected(Error(ErrorType::MISSING_RIGHT_PAREN, -1));
    }
    if (equation.empty()) {
        return {};
    }

    switch (equation.front().type) {
        case TokenType::ADD_OP:
            equation.erase(equation.begin());
            break;
        case TokenType::SUB_OP:
            equation.erase(equation.begin());
            equation.front().value = -equation.front().value;
            break;
        case TokenType::RATIONAL:
            break;
        default:
            return std::unexpected(Error(ErrorType::UNEXPECTED_TOKEN, equation.front().pos));
    }
    for (int i = 0; i + 1 < equation.size(); ++i) {
        switch (equation.at(i).type) {
            case TokenType::ADD_OP:
                switch (equation.at(i + 1).type) {
                    case TokenType::SUB_OP:
                        equation.erase(equation.begin() + i--);
                        break;
                    case TokenType::RATIONAL:
                        break;
                    default:
                        return std::unexpected(Error(ErrorType::UNEXPECTED_TOKEN, equation.at(i + 1).pos));
                }
                break;
            case TokenType::SUB_OP:
                switch (equation.at(i + 1).type) {
                    case TokenType::ADD_OP:
                        equation.erase(equation.begin() + 1 + i--);
                        break;
                    case TokenType::SUB_OP:
                        equation.at(i).type = TokenType::ADD_OP;
                        equation.erase(equation.begin() + 1 + i--);
                        break;
                    case TokenType::RATIONAL:
                        break;
                    default:
                        return std::unexpected(Error(ErrorType::UNEXPECTED_TOKEN, equation.at(i + 1).pos));
                }
                break;
            case TokenType::DIV_OP:
            case TokenType::MUL_OP:
                switch (equation.at(i + 1).type) {
                    case TokenType::ADD_OP:
                        equation.erase(equation.begin() + 1 + i--);
                        break;
                    case TokenType::SUB_OP:
                        if (equation.size() <= i + 2) {
                            return std::unexpected(Error(ErrorType::MISSING_END, equation.at(i).pos + 1));
                        }
                        if (equation.at(i + 2).type == TokenType::RATIONAL) {
                            equation.at(i + 2).value = -equation.at(i + 2).value;
                            equation.erase(equation.begin() + 1 + i--);
                        } else {
                            return std::unexpected(Error(ErrorType::UNEXPECTED_TOKEN, equation.at(i + 2).pos));
                        }
                        break;
                    case TokenType::RATIONAL:
                        break;
                    default:
                        return std::unexpected(Error(ErrorType::UNEXPECTED_TOKEN, equation.at(i + 1).pos));
                }
                break;
            case TokenType::RATIONAL:
                if (equation.at(i + 1).type == TokenType::LEFT_PAREN ||
                    equation.at(i + 1).type == TokenType::RIGHT_PAREN) {
                    return std::unexpected(Error(ErrorType::UNEXPECTED_TOKEN, equation.at(i + 1).pos));
                }
                if (equation.at(i + 1).type == TokenType::RATIONAL) {
                    equation.insert(equation.begin() + i + 1, Token(TokenType::MUL_OP, -1));
                    i++;
                }
                break;
            default:
                return std::unexpected(Error(ErrorType::LOGIC_ERROR, -1));
        }
    }
    if (equation.back().type != TokenType::RATIONAL) {
        return std::unexpected(Error(ErrorType::MISSING_END, equation.back().pos + 1));
    }

    auto eval = [&](const std::set<TokenType> &operations) -> std::optional<Error> {
        for (int i = 0; i < ((int) equation.size()) - 2;) {
            switch (equation.at(i + 1).type) {
                case TokenType::ADD_OP:
                    if (operations.contains(TokenType::ADD_OP)) {
                        equation.at(i).value = equation.at(i + 2).value + equation.at(i).value;
                        equation.erase(equation.begin() + i + 1, equation.begin() + i + 3);
                    } else {
                        i += 2;
                    }
                    break;
                case TokenType::SUB_OP:
                    if (operations.contains(TokenType::SUB_OP)) {
                        equation.at(i).value = equation.at(i + 2).value - equation.at(i).value;
                        equation.erase(equation.begin() + i + 1, equation.begin() + i + 3);
                    } else {
                        i += 2;
                    }
                    break;
                case TokenType::MUL_OP:
                    if (operations.contains(TokenType::MUL_OP)) {
                        equation.at(i).value = equation.at(i + 2).value * equation.at(i).value;
                        equation.erase(equation.begin() + i + 1, equation.begin() + i + 3);
                    } else {
                        i += 2;
                    }
                    break;
                case TokenType::DIV_OP:
                    if (operations.contains(TokenType::DIV_OP)) {
                        equation.at(i).value = equation.at(i + 2).value / equation.at(i).value;
                        if (equation.at(i).value.get_den() == 0) {
                            return Error(ErrorType::ZERO_DIVISION, equation.at(i + 1).pos);
                        }
                        equation.erase(equation.begin() + i + 1, equation.begin() + i + 3);
                    } else {
                        i += 2;
                    }
                    break;
                default:
                    return Error(ErrorType::LOGIC_ERROR, -1);
            }
        }
        return {};
    };
    if (auto err = eval({TokenType::MUL_OP, TokenType::DIV_OP})) {
        return std::unexpected(*err);
    }
    if (auto err = eval({TokenType::ADD_OP, TokenType::SUB_OP})) {
        return std::unexpected(*err);
    }
    return equation.at(0).value;
}

auto calculator::evaluate_string(const std::string &str) -> std::expected<RationalNumber, Error> {
    auto parsed_str = parse_string(str);
    if (!parsed_str) {
        return std::unexpected(Error(ErrorType::INVALID_STRING, parsed_str.error()));
    }
    return evaluate_equation(*parsed_str);
}