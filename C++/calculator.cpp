// ======================================================================
// calculator.cpp
// 
// Implementation of the recursive descent calculator.
// Supports: +, -, *, /, parentheses, and unary minus.
// Numbers may contain a decimal point.
// ======================================================================

#include "calculator.h"
#include <sstream>
#include <cctype>
#include <cmath>

namespace {
    // Current input stream for parsing
    std::istringstream* input = nullptr;

    // Skip whitespace
    void skip_ws() {
        while (input->good() && std::isspace(input->peek()))
            input->get();
    }

    // Forward declarations
    double expr();
    double term();
    double factor();

    // expr = term {('+' | '-') term}
    double expr() {
        double left = term();
        skip_ws();
        while (input->good()) {
            char op = input->peek();
            if (op == '+' || op == '-') {
                input->get();
                double right = term();
                if (op == '+')
                    left += right;
                else
                    left -= right;
                skip_ws();
            } else {
                break;
            }
        }
        return left;
    }

    // term = factor {('*' | '/') factor}
    double term() {
        double left = factor();
        skip_ws();
        while (input->good()) {
            char op = input->peek();
            if (op == '*' || op == '/') {
                input->get();
                double right = factor();
                if (op == '*')
                    left *= right;
                else {
                    if (right == 0.0)
                        throw std::runtime_error("Division by zero");
                    left /= right;
                }
                skip_ws();
            } else {
                break;
            }
        }
        return left;
    }

    // factor = number | '(' expr ')' | '-' factor
    double factor() {
        skip_ws();
        if (!input->good())
            throw std::runtime_error("Unexpected end of input");

        char c = input->peek();

        if (c == '(') {
            input->get();               // consume '('
            double val = expr();
            skip_ws();
            if (input->get() != ')')
                throw std::runtime_error("Expected ')'");
            return val;
        } else if (c == '-') {
            input->get();               // unary minus
            return -factor();
        } else {
            // Number
            double val;
            (*input) >> val;
            if (input->fail())
                throw std::runtime_error("Expected a number");
            return val;
        }
    }
} // anonymous namespace

double evaluate(const std::string& expression) {
    std::istringstream iss(expression);
    input = &iss;
    double result = expr();
    skip_ws();
    if (input->good())
        throw std::runtime_error("Unexpected trailing characters");
    return result;
}
