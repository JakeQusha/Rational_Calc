#pragma once
#include <string>

class RationalNumber {
    int numerator;
    int denominator;
protected:
    void try_reduce();
public:
    RationalNumber(int numerator, int denominator);
    RationalNumber() = delete;
    std::string get_number() const;
    void operator ++();
    void operator ++(int);
    RationalNumber operator +(const RationalNumber& other) const;
    RationalNumber operator -(const RationalNumber& other) const;
    RationalNumber operator *(const RationalNumber& other) const;
    RationalNumber operator /(const RationalNumber& other) const;


    friend std::ostream& operator << (std::ostream& outs,const RationalNumber &value);

};


