#include "RationalNumber.h"
#include <format>

RationalNumber::RationalNumber() : numerator(0), denominator(1) {}

RationalNumber::RationalNumber(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
    this->try_reduce();
}

void RationalNumber::operator++() {
    numerator += denominator;
    this->try_reduce();
}

static auto gcd(const int num, const int den) -> int {
    return den == 0 ? std::max(num, -num) : gcd(den, num % den);
}

void RationalNumber::try_reduce() {
    if (this->denominator < 0) {
        this->numerator = -this->denominator;
        this->denominator = std::abs(this->denominator);
    }
    int gc = gcd(this->numerator, this->denominator);
    this->numerator /= gc;
    this->denominator /= gc;

}

RationalNumber RationalNumber::operator+(const RationalNumber &other) const {
    return {this->numerator * other.denominator + other.numerator * this->denominator,
            this->denominator * other.denominator};
}

std::string RationalNumber::get_number_str() const {
    if (this->denominator == 1)
        return std::format("{}", this->numerator);
    return std::format("{}/{}", this->numerator, this->denominator);
}

void RationalNumber::operator++(int) {
    numerator += denominator;
    this->try_reduce();
}

RationalNumber RationalNumber::operator-(const RationalNumber &other) const {
    return {other.numerator * this->denominator - this->numerator * other.denominator,
            this->denominator * other.denominator};
}

RationalNumber RationalNumber::operator*(const RationalNumber &other) const {
    return {this->numerator * other.numerator, this->denominator * other.denominator};
}

RationalNumber RationalNumber::operator/(const RationalNumber &other) const {
    return {this->denominator * other.numerator, this->numerator * other.denominator};
}

std::ostream &operator<<(std::ostream &outs, const RationalNumber &value) {
    return outs << value.get_number_str();
}

RationalNumber RationalNumber::operator-() const {
    return {-numerator, denominator};
}

int RationalNumber::get_num() const {
    return numerator;
}

int RationalNumber::get_den() const {
    return denominator;
}


