#include <iostream>
#include "RationalNumber.h"
RationalNumber calculate(std::string ex){
    //handle braces
    int counter =0;
    int start;
    for(int i=0;i<ex.size();++i){
        if (ex[i] == '('){
            counter ++;
            start = i+1;
            i++;
            while (counter>0)
            {
                if (i>=ex.size())
                {
                    std::cout<<"inwalida";
                    exit(1);
                }
                switch (ex[i]) {
                    case '(':
                        counter++;
                        break;
                    case ')':
                        counter--;
                        break;
                    default:
                        break;
                }
                i++;
            }
            //std::cout<<ex.substr(start,i-start-1 )<<"\n";
            ex.replace(start-1,i-start+1,calculate(ex.substr(start,i-start-1)).get_number());
            //std::cout<<ex<<"\n";
        }
    }
    //solve TODO
    for (auto &x : ex){

      while (isdigit(x)){

      }
    }
    return {1,1};
}
int main() {
    std::string str;
    while(std::cin){
        getline(std::cin,str);
        if(str=="exit") break;
        std::cout<<calculate(str)<<std::endl;
    }
}
