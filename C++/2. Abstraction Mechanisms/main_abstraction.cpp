// ======================================================================
// main_abstraction.cpp
// 
// Educational walk‑through of all abstraction mechanisms.
// ======================================================================

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <typeinfo>
#include <cmath>

#include "rational.h"
#include "shapes.h"
#include "vector.h"      // our RAII vector template
#include "array.h"
#include "stack.h"
#include "matrix.h"
#include "demo_templates.h"

// ----------------------------------------------------------------------
// Mini demos for each section
// ----------------------------------------------------------------------

void demo_rational() {
    std::cout << "\n========== Rational Numbers ==========\n";
    Rational r1(1, 3);
    Rational r2(2, 6);   // should reduce to 1/3
    std::cout << "r1 = " << r1 << ", r2 = " << r2 << '\n';
    std::cout << "r1 == r2: " << (r1 == r2) << '\n';

    Rational sum = r1 + Rational(1, 2);
    std::cout << "1/3 + 1/2 = " << sum << " = " << sum.toDouble() << '\n';

    Rational prod = r1 * Rational(3, 4);
    std::cout << "1/3 * 3/4 = " << prod << '\n';

    // I/O
    std::cout << "Enter a rational (n/d): ";
    Rational input;
    std::cin >> input;
    std::cout << "You entered: " << input << '\n';
}

void demo_shapes() {
    std::cout << "\n========== Shape Hierarchy ==========\n";

    // Create a polymorphic collection using smart pointers
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    shapes.push_back(std::make_unique<Triangle>(3.0, 4.0));

    std::cout << "Drawing all shapes:\n";
    drawAll(shapes, std::cout);
    std::cout << "Total area: " << totalArea(shapes) << '\n';

    // Clone a shape
    auto clonedCircle = shapes[0]->clone();
    std::cout << "Cloned circle area: " << clonedCircle->area() << '\n';

    // dynamic_cast and typeid
    for (const auto& sp : shapes) {
        std::cout << "typeid name: " << typeid(*sp).name() << '\n';
        if (dynamic_cast<Circle*>(sp.get())) {
            std::cout << "  This is a Circle with radius "
                      << dynamic_cast<Circle&>(*sp).radius() << '\n';
        }
    }

    // Object slicing prevention (using references/pointers)
    Circle c(10.0);
    Shape& ref = c;              // OK, reference to base
    ref.print();                 // calls Circle::print via virtual dispatch
    // Shape slice = c;          // This would slice, but we don't do it.
}

void demo_vector_and_exception_safety() {
    std::cout << "\n========== Vector (RAII) & Exception Safety ==========\n";
    try {
        Vector<int> v1(3, 10);   // 3 elements of value 10
        std::cout << "v1 size: " << v1.size() << '\n';
        for (std::size_t i = 0; i < v1.size(); ++i) std::cout << v1[i] << ' ';
        std::cout << '\n';

        Vector<int> v2 = v1;      // copy constructor
        v2.push_back(99);
        std::cout << "After push_back: ";
        for (std::size_t i = 0; i < v2.size(); ++i) std::cout << v2[i] << ' ';
        std::cout << '\n';

        // Copy‑and‑swap assignment (strong guarantee)
        Vector<int> v3;
        v3 = v2;                   // exception safe
        std::cout << "v3[0] = " << v3[0] << '\n';

        // pop_back
        v3.pop_back();
        std::cout << "After pop, v3 size = " << v3.size() << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << '\n';
    }
}

void demo_template_functions() {
    std::cout << "\n========== Function Templates ==========\n";
    std::cout << "max(3, 7) = " << max(3, 7) << '\n';
    std::cout << "max(3.14, 2.71) = " << max(3.14, 2.71) << '\n';

    // Specialization for C‑strings
    const char* s1 = "apple";
    const char* s2 = "banana";
    std::cout << "max(\"apple\", \"banana\") = " << max(s1, s2) << '\n';

    // Generic swap
    int a = 5, b = 10;
    swap(a, b);
    std::cout << "After swap: a=" << a << ", b=" << b << '\n';

    // find
    int arr[] = {1, 2, 3, 4, 5};
    auto it = find(arr, arr + 5, 3);
    if (it != arr + 5)
        std::cout << "Found 3 at position " << (it - arr) << '\n';
}

void demo_array_and_stack() {
    std::cout << "\n========== Array (non‑type param) & Stack ==========\n";
    Array<int, 5> arr;
    arr[0] = 10; arr[1] = 20;
    for (std::size_t i = 0; i < arr.size(); ++i) std::cout << arr[i] << ' ';
    std::cout << '\n';

    // Specialized Array<bool, 8>
    Array<bool, 8> bits;
    // bits[0] = true; // (not fully implemented; just a demo of specialization)

    Stack<std::string> stack;
    stack.push("hello");
    stack.push("world");
    while (!stack.empty()) {
        std::cout << stack.top() << '\n';
        stack.pop();
    }
}

void demo_matrix() {
    std::cout << "\n========== Matrix ==========\n";
    Matrix<int, 2, 3> m1;
    m1(0,0) = 1; m1(0,1) = 2; m1(0,2) = 3;
    m1(1,0) = 4; m1(1,1) = 5; m1(1,2) = 6;
    std::cout << "m1:\n" << m1;

    Matrix<int, 2, 3> m2;
    m2(0,0) = 6; m2(0,1) = 5; m2(0,2) = 4;
    m2(1,0) = 3; m2(1,1) = 2; m2(1,2) = 1;
    std::cout << "m1 + m2:\n" << (m1 + m2);
    std::cout << "2 * m1:\n" << (2 * m1);
}

// ----------------------------------------------------------------------
// Main: run all demos
// ----------------------------------------------------------------------
int main() {
    std::cout << "C++ Abstraction Mechanisms Educational Demo\n";
    std::cout << "============================================\n";

    demo_rational();
    demo_shapes();
    demo_vector_and_exception_safety();
    demo_template_functions();
    demo_array_and_stack();
    demo_matrix();

    return 0;
}