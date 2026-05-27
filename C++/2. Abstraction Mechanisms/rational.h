// ======================================================================
// rational.h
// 
// A Rational number class demonstrating:
// - Constructors (default, parameterized, copy)
// - Member initializer lists
// - Operator overloading (member and non-member)
// - const member functions
// - Stream I/O operators
// - Reduction to lowest terms
// ======================================================================

#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <stdexcept>
#include <numeric>   // std::gcd

class Rational {
public:
    // Constructors
    Rational() : num_(0), den_(1) {}
    Rational(int n, int d);
    explicit Rational(int n) : num_(n), den_(1) {}   // explicit to avoid unintended conversions

    // Copy constructor (compiler generated is fine, but we can be explicit)
    Rational(const Rational&) = default;
    Rational& operator=(const Rational&) = default;

    // Arithmetic operators (members often return *this for chaining)
    Rational& operator+=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);

    // Unary minus
    Rational operator-() const;

    // Accessors
    int numerator() const { return num_; }
    int denominator() const { return den_; }

    // Conversion to double (for convenience)
    double toDouble() const { return static_cast<double>(num_) / den_; }

private:
    int num_;
    int den_;

    void reduce();   // normalize sign and reduce fraction
};

// Non-member binary operators (usually implemented in terms of member += etc.)
Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);

// Comparison operators
bool operator==(const Rational& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
bool operator<(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);

// Stream I/O
std::ostream& operator<<(std::ostream& os, const Rational& r);
std::istream& operator>>(std::istream& is, Rational& r);

#endif // RATIONAL_H