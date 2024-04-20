#include <iostream>
#include "RationalNumber.h"
#include "calc.h"

auto main() -> int {
    std::string str;
    while (std::cin) {
        getline(std::cin, str);
        if (str == "exit") { break; }
        auto under = [](int off) -> std::string {
            std::string ret;
            for (int i = 0; i < off; ++i)ret += '-';
            ret += '^';
            return ret;
        };
        auto tokens = tokenizer::parse_string(str);
        if (!tokens) {
            std::cerr << "Illegal Character:" << std::endl << str << std::endl << under(tokens.error()) << std::endl;
            continue;

        }
        auto result = calculator::evaluate_equation(*tokens);
        if (result) {
            std::cout << *result << std::endl;
            continue;
        }
        switch (result.error().type) {
            case calculator::ErrorType::INVALID_STRING:
                std::cerr << "Illegal Character:" << std::endl << str << std::endl << under(result.error().where) << std::endl;
                break;
            case calculator::ErrorType::UNEXPECTED_RIGHT_PAREN:
                std::cerr << "Unexpected Closing Parenthesis:" << std::endl << str << std::endl << under(result.error().where) << std::endl;
                break;
            case calculator::ErrorType::MISSING_RIGHT_PAREN:
                std::cerr << "Missing Closing Parenthesis:" << std::endl << str << std::endl << under((int)str.size()) << std::endl;
                break;
            case calculator::ErrorType::UNEXPECTED_TOKEN:
                std::cerr << "Unexpected Operator:" << std::endl << str << std::endl << under(result.error().where) << std::endl;
                break;
            case calculator::ErrorType::MISSING_END:
                std::cerr << "Missing Number After Operator:" << std::endl << str << std::endl << under(result.error().where) << std::endl;
                break;
            case calculator::ErrorType::LOGIC_ERROR:
                std::cerr << "Logic Error"<<std::endl;
                break;
        }
    }
}
