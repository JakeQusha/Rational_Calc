#include <iostream>
#include "RationalNumber.h"
#include "calc.h"
auto main() -> int {
    std::string str;
    while (std::cin) {
        getline(std::cin, str);
        if (str == "exit") { break;}
        auto tokens = tokenizer::parse_string(str);
        if(tokens.has_value())
        {
            std::cout<<calculator::evaluate_equation(*tokens)<<std::endl;
        } else{
            auto under = [](int off)->std::string {std::string ret; for(int i=0;i<off;++i)ret+='-';ret+='^';return ret;};
            std::cerr<<"Unexpected Character:"<<std::endl<<str<<std::endl<<under(tokens.error())<<std::endl;
        }
    }
}
