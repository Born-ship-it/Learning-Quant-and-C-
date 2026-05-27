// ======================================================================
// rational.cpp
// ======================================================================

#include "rational.h"
#include <cmath>
#include <cstdlib>   // abs

// Helper: greatest common divisor
static int gcd(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void Rational::reduce() {
    if (den_ == 0)
        throw std::invalid_argument("Denominator cannot be zero");
    // Ensure denominator is positive; if negative, flip sign
    if (den_ < 0) {
        num_ = -num_;
        den_ = -den_;
    }
    int g = gcd(num_, den_);
    num_ /= g;
    den_ /= g;
}

Rational::Rational(int n, int d) : num_(n), den_(d) {
    reduce();
}

Rational& Rational::operator+=(const Rational& rhs) {
    // a/b + c/d = (a*d + b*c) / (b*d)
    num_ = num_ * rhs.den_ + den_ * rhs.num_;
    den_ = den_ * rhs.den_;
    reduce();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
    num_ = num_ * rhs.den_ - den_ * rhs.num_;
    den_ = den_ * rhs.den_;
    reduce();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
    num_ *= rhs.num_;
    den_ *= rhs.den_;
    reduce();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.num_ == 0)
        throw std::invalid_argument("Division by zero");
    num_ *= rhs.den_;
    den_ *= rhs.num_;
    reduce();
    return *this;
}

Rational Rational::operator-() const {
    return Rational(-num_, den_);
}

// Non-member operators
Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational temp = lhs;
    temp += rhs;
    return temp;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational temp = lhs;
    temp -= rhs;
    return temp;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational temp = lhs;
    temp *= rhs;
    return temp;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational temp = lhs;
    temp /= rhs;
    return temp;
}

// Comparisons
bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator() == rhs.numerator() &&
           lhs.denominator() == rhs.denominator();
}

bool operator!=(const Rational& lhs, const Rational& rhs) { return !(lhs == rhs); }

bool operator<(const Rational& lhs, const Rational& rhs) {
    // Cross-multiply without overflow risk is tricky, for demo we use double
    return lhs.toDouble() < rhs.toDouble();
}
bool operator<=(const Rational& lhs, const Rational& rhs) { return !(rhs < lhs); }
bool operator>(const Rational& lhs, const Rational& rhs)  { return rhs < lhs; }
bool operator>=(const Rational& lhs, const Rational& rhs) { return !(lhs < rhs); }

// Stream output
std::ostream& operator<<(std::ostream& os, const Rational& r) {
    os << r.numerator() << '/' << r.denominator();
    return os;
}

// Stream input
std::istream& operator>>(std::istream& is, Rational& r) {
    int n, d;
    char slash;
    is >> n >> slash >> d;
    if (slash != '/') {
        is.setstate(std::ios::failbit);
        return is;
    }
    r = Rational(n, d);
    return is;
}