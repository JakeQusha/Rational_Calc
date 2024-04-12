#include <iostream>
#include "RationalNumber.h"
#include "tokenizer.h"
auto main() -> int {
    std::string str;
    while (std::cin) {
        getline(std::cin, str);
        if (str == "exit") { break;}
        auto tokens = tokenizer::parse_string(str);
        for (auto x : tokens){
            switch (x.type) {
                case tokenizer::TokenType::RATIONAL:
                    std::cout<<'{'<<x.value<<"} ";
                    break;
                default:
                    std::cout<< static_cast<int>(x.type)<<" ";
            }
        }
        std::cout<<std::endl;
    }
}
