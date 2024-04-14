#include <iostream>
#include "RationalNumber.h"
#include "tokenizer.h"
#include "calc.h"
auto main() -> int {
    std::string str;
    while (std::cin) {
        getline(std::cin, str);
        if (str == "exit") { break;}
        auto tokens = tokenizer::parse_string(str);
        std::cout<<calculator::evaluate_equation(tokens)<<std::endl;
    }
}
