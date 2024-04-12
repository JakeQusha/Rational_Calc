#include "RationalNumber.h"
#include <format>
RationalNumber::RationalNumber(int numerator, int denominator)
{
this->numerator = numerator;
this->denominator = denominator;
try_reduce();
}

void RationalNumber::operator++() {
    numerator+=denominator;
    this->try_reduce();
}
void RationalNumber::try_reduce() {
    for (int i = 2; i <= std::min(this->numerator, this->denominator); ++i) {
        while (this->numerator%i== 0 && this->denominator%i == 0){
            this->numerator/=i;
            this->denominator/=i;
        }
    }
}

RationalNumber RationalNumber::operator+(const RationalNumber& other) const {
    return {this->numerator*other.denominator+other.numerator* this->denominator,this->denominator*other.denominator};
}

std::string RationalNumber::get_number_str() const {
    return std::format("{} / {}", this->numerator, this->denominator);
}

void RationalNumber::operator++(int) {
    numerator+=denominator;
    this->try_reduce();
}

RationalNumber RationalNumber::operator-(const RationalNumber &other) const {
    return {this->numerator*other.denominator-other.numerator* this->denominator,this->denominator*other.denominator};
}

RationalNumber RationalNumber::operator*(const RationalNumber &other) const {
    return {this->numerator*other.numerator, this->denominator*other.denominator};
}

RationalNumber RationalNumber::operator/(const RationalNumber &other) const {
    return {this->numerator*other.denominator, this->denominator*other.numerator};
}

std::ostream &operator<<(std::ostream &outs, const RationalNumber &value) {
   outs<< value.get_number_str();
    return outs;
}
