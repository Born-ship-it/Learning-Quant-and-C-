// ======================================================================
// calculator.h
// 
// Header file for the recursive descent calculator.
// Demonstrates multi‑file project organization, inclusion guards,
// and exception usage.
// ======================================================================

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <stdexcept>

// Parses the whole input string and returns the result.
// Throws std::runtime_error on syntax error or math error.
double evaluate(const std::string& expression);

#endif // CALCULATOR_H
