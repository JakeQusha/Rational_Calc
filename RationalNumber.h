#pragma once
#include <string>

class RationalNumber {
    int numerator;
    int denominator;
protected:
    void try_reduce();
public:
    RationalNumber(int numerator, int denominator);
    RationalNumber() = default;
    [[nodiscard]] std::string get_number_str() const;
    void operator ++();
    void operator ++(int);
    RationalNumber operator +(const RationalNumber& other) const;
    RationalNumber operator -(const RationalNumber& other) const;
    RationalNumber operator *(const RationalNumber& other) const;
    RationalNumber operator /(const RationalNumber& other) const;
    friend auto operator << (std::ostream& outs,const RationalNumber &value) -> std::ostream&;
};


