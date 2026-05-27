// ======================================================================
// foundation_demo.cpp
// 
// A comprehensive educational demonstration covering all points in:
// Foundation – Basic Types, Control Flow, and Program Structure
// 
// Compile (with all files in the same directory):
//   g++ -std=c++17 -o foundation_demo foundation_demo.cpp calculator.cpp
//   ./foundation_demo
// ======================================================================

#include <iostream>
#include <stdexcept>
#include <cstring>      // for C‑style strings
#include <cmath>        // for fmod, pow, ...
#include <limits>       // for numeric_limits
#include <sstream>      // for stringstream in calculator
#include "calculator.h" // our multi‑file project header

// ----------------------------------------------------------------------
// 1. Fundamental types – practice with all built‑in types
// ----------------------------------------------------------------------
void demo_fundamental_types() {
    std::cout << "=== Fundamental Types ===\n";

    // Integer types
    int      i = 42;
    short    s = 32767;
    long     l = 100000L;
    long long ll = 123456789012345LL;
    unsigned int ui = 3000000000U;

    // Floating‑point types
    float       f = 3.14159f;
    double      d = 2.718281828;
    long double ld = 1.4142135623730951L;

    // Character types
    char        c = 'A';
    wchar_t     wc = L'Ω';  // wide character
    char16_t    u16 = u'∑'; // UTF‑16
    char32_t    u32 = U'∑'; // UTF‑32

    // Boolean
    bool flag = true;

    std::cout << "int: " << i << "  size: " << sizeof(i) << " bytes\n";
    std::cout << "double: " << d << "  size: " << sizeof(d) << " bytes\n";
    std::cout << "char: " << c << "  size: " << sizeof(c) << " byte\n";
    std::cout << "bool: " << flag << "  size: " << sizeof(flag) << " byte\n";
    std::cout << "sizeof(long double): " << sizeof(ld) << " bytes\n";
    std::cout << "Minimum int: " << std::numeric_limits<int>::min() << '\n';
    std::cout << "Maximum int: " << std::numeric_limits<int>::max() << "\n\n";
}

// ----------------------------------------------------------------------
// 2. Expressions and operators
// ----------------------------------------------------------------------
void demo_operators() {
    std::cout << "=== Operators ===\n";

    int a = 10, b = 3;
    std::cout << "a = " << a << ", b = " << b << '\n';

    // Arithmetic
    std::cout << "a + b = " << (a + b) << '\n';
    std::cout << "a / b = " << (a / b) << " (integer division)\n";
    std::cout << "a % b = " << (a % b) << " (modulus)\n";

    // Relational
    std::cout << "a == b: " << (a == b) << '\n';
    std::cout << "a != b: " << (a != b) << '\n';

    // Logical
    bool t = true, f = false;
    std::cout << "t && f: " << (t && f) << '\n';
    std::cout << "t || f: " << (t || f) << '\n';
    std::cout << "!f: " << (!f) << '\n';

    // Bitwise
    int x = 0b1100, y = 0b1010;  // binary literals (C++14)
    std::cout << "x & y (bitwise AND): " << (x & y) << " (binary " << std::bitset<4>(x & y) << ")\n";
    std::cout << "x | y (bitwise OR):  " << (x | y) << " (binary " << std::bitset<4>(x | y) << ")\n";
    std::cout << "x ^ y (bitwise XOR): " << (x ^ y) << " (binary " << std::bitset<4>(x ^ y) << ")\n";
    std::cout << "~x (bitwise NOT):   " << (~x) << " (binary " << std::bitset<32>(~x) << ")\n";

    // Assignment and compound
    int z = 5;
    z += 3;  // z = z + 3
    std::cout << "z after += 3: " << z << '\n';

    // Conditional (ternary)
    int min_val = (a < b) ? a : b;
    std::cout << "min(a,b) using ternary: " << min_val << "\n\n";
}

// ----------------------------------------------------------------------
// 3. Branching: if, else if, switch, conditional operator
// ----------------------------------------------------------------------
void demo_branching() {
    std::cout << "=== Branching ===\n";

    int value = 7;
    if (value < 0) {
        std::cout << "negative\n";
    } else if (value == 0) {
        std::cout << "zero\n";
    } else {
        std::cout << "positive\n";
    }

    // switch with fall‑through and break
    int option = 2;
    switch (option) {
        case 1:
            std::cout << "One ";
            break;
        case 2:
            std::cout << "Two ";
            // intentional fall‑through
        case 3:
            std::cout << "or Three\n";
            break;
        default:
            std::cout << "Other\n";
            break;
    }

    // Using the conditional operator inside an expression
    std::cout << "value is " << (value % 2 == 0 ? "even" : "odd") << "\n\n";
}

// ----------------------------------------------------------------------
// 4. Loops: for, while, do‑while, and understanding iteration
// ----------------------------------------------------------------------
void demo_loops() {
    std::cout << "=== Loops ===\n";

    // Classic for
    std::cout << "for loop: ";
    for (int i = 0; i < 5; ++i)
        std::cout << i << ' ';
    std::cout << '\n';

    // while
    int cnt = 5;
    std::cout << "while loop: ";
    while (cnt > 0) {
        std::cout << cnt << ' ';
        --cnt;
    }
    std::cout << '\n';

    // do‑while (executes at least once)
    std::cout << "do-while: ";
    int n = 0;
    do {
        std::cout << n << ' ';
        ++n;
    } while (n < 3);
    std::cout << '\n';

    // Range‑based for (over arrays)
    int arr[] = {10, 20, 30, 40};
    std::cout << "range-based for: ";
    for (int elem : arr)
        std::cout << elem << ' ';
    std::cout << "\n\n";
}

// ----------------------------------------------------------------------
// 5. Arrays and pointers – array traversal, pointer arithmetic
// ----------------------------------------------------------------------
void demo_arrays_and_pointers() {
    std::cout << "=== Arrays & Pointers ===\n";

    int nums[5] = {1, 2, 3, 4, 5};

    // Array name decays to pointer
    int* p = nums;  // points to first element
    std::cout << "First element: " << *p << '\n';

    // Pointer arithmetic
    std::cout << "Third element via p+2: " << *(p + 2) << '\n';

    // Iterate array with pointer
    std::cout << "Array via pointer: ";
    for (int* ptr = nums; ptr != nums + 5; ++ptr)
        std::cout << *ptr << ' ';
    std::cout << '\n';

    // Multidimensional array and pointer
    int matrix[2][3] = {{1,2,3},{4,5,6}};
    int (*mp)[3] = matrix;  // pointer to array[3] of int
    std::cout << "matrix[1][2] = " << mp[1][2] << '\n';

    // Dynamic allocation with new and delete
    int* dynArr = new int[3]{100, 200, 300};
    std::cout << "Dynamic array: ";
    for (int i = 0; i < 3; ++i) std::cout << dynArr[i] << ' ';
    std::cout << '\n';
    delete[] dynArr;
    std::cout << '\n';
}

// ----------------------------------------------------------------------
// 6. C‑style strings and relationship to pointers
// ----------------------------------------------------------------------
void demo_c_strings() {
    std::cout << "=== C‑style Strings ===\n";

    const char* greeting = "Hello";          // string literal, pointer to first char
    char name[] = "World";                   // array, null‑terminated

    std::cout << "greeting: " << greeting << " (pointer)\n";
    std::cout << "name: " << name << " (array)\n";

    // Access individual characters
    std::cout << "First char: " << *greeting << ", Second: " << *(greeting+1) << '\n';

    // Some <cstring> functions
    char buffer[20];
    std::strcpy(buffer, greeting);
    std::strcat(buffer, " ");
    std::strcat(buffer, name);
    std::cout << "Concatenated: " << buffer << '\n';
    std::cout << "Length: " << std::strlen(buffer) << '\n';

    // Comparing strings
    if (std::strcmp(greeting, "Hello") == 0)
        std::cout << "greeting equals \"Hello\"\n";
    std::cout << '\n';
}

// ----------------------------------------------------------------------
// 7. Simple structs
// ----------------------------------------------------------------------
struct Point {
    double x, y;
};

// struct with member function
struct Rectangle {
    Point topLeft;
    double width, height;

    double area() const {
        return width * height;
    }
};

void demo_structs() {
    std::cout << "=== Structs ===\n";

    Point p1 = {3.0, 4.0};
    Point p2{5.5, 2.2};  // uniform initialisation
    std::cout << "p1: (" << p1.x << ", " << p1.y << ")\n";

    Rectangle rect = {{1.0, 5.0}, 10.0, 4.0};
    std::cout << "Rectangle area: " << rect.area() << '\n';

    // Default memberwise copy
    Point p3 = p1;
    std::cout << "p3 (copy of p1): (" << p3.x << ", " << p3.y << ")\n\n";
}

// ----------------------------------------------------------------------
// 8. Functions: pass by value, pointer, reference, return values,
//    overloading, default arguments
// ----------------------------------------------------------------------

// Pass by value
double square_val(double x) {
    return x * x;
}

// Pass by pointer (modify original)
void negate_ptr(int* p) {
    if (p) *p = -*p;
}

// Pass by reference (modify original)
void negate_ref(int& r) {
    r = -r;
}

// Const reference – avoids copy, read‑only
double distance(const Point& p) {
    return std::sqrt(p.x * p.x + p.y * p.y);
}

// Overloaded functions (same name, different parameters)
void print(int v) {
    std::cout << "int: " << v << '\n';
}
void print(double v) {
    std::cout << "double: " << v << '\n';
}
void print(const char* v) {
    std::cout << "C-string: " << v << '\n';
}

// Default arguments
void greet(const char* name = "Guest") {
    std::cout << "Hello, " << name << "!\n";
}

void demo_functions() {
    std::cout << "=== Functions ===\n";

    // Value
    std::cout << "square_val(5) = " << square_val(5) << '\n';

    // Pointer
    int a = 10;
    negate_ptr(&a);
    std::cout << "After negate_ptr: " << a << '\n';

    // Reference
    int b = 7;
    negate_ref(b);
    std::cout << "After negate_ref: " << b << '\n';

    // Const reference with struct
    Point p{3.0, 4.0};
    std::cout << "Distance to origin: " << distance(p) << '\n';

    // Overloading
    print(42);
    print(3.14159);
    print("Hello");

    // Default arguments
    greet();
    greet("Alice");
    std::cout << '\n';
}

// ----------------------------------------------------------------------
// 9. Scope and storage duration, static keyword
// ----------------------------------------------------------------------

int global_var = 100;  // static storage, external linkage by default

void demo_scope_and_static() {
    std::cout << "=== Scope & Static ===\n";

    int local_var = 10;  // automatic storage
    std::cout << "local_var: " << local_var << '\n';
    std::cout << "global_var: " << global_var << '\n';

    // Static local variable – persists across calls
    static int call_count = 0;
    ++call_count;
    std::cout << "This function has been called " << call_count << " time(s)\n";

    // Block scope masking
    int x = 5;
    {
        int x = 99;
        std::cout << "Inner x: " << x << '\n';  // 99
    }
    std::cout << "Outer x: " << x << "\n\n";    // 5
}

// ----------------------------------------------------------------------
// 10. Namespaces – avoid name collisions
// ----------------------------------------------------------------------

namespace MathUtils {
    const double PI = 3.141592653589793;

    double areaOfCircle(double radius) {
        return PI * radius * radius;
    }
}

namespace Printer {
    void print(double d) {
        std::cout << "Printer: " << d << '\n';
    }
}

void demo_namespaces() {
    std::cout << "=== Namespaces ===\n";

    using MathUtils::PI;
    std::cout << "PI: " << PI << '\n';
    std::cout << "Area of circle r=2: " << MathUtils::areaOfCircle(2.0) << '\n';

    // Disambiguation
    Printer::print(3.14);
    ::print(3.14); // global print(double)
    std::cout << '\n';
}

// ----------------------------------------------------------------------
// 11. Exception handling: throw, try, catch, resource cleanup
// ----------------------------------------------------------------------

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource released\n"; }
};

int divide(int a, int b) {
    if (b == 0) throw std::runtime_error("Division by zero");
    return a / b;
}

void demo_exceptions() {
    std::cout << "=== Exception Handling ===\n";

    // Simple exception
    try {
        divide(10, 0);
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << '\n';
    }

    // RAII cleanup with local object
    try {
        Resource res;
        // even if this throws, Resource is destroyed
        throw std::runtime_error("Something went wrong");
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << " – and Resource was released.\n";
    }

    std::cout << '\n';
}

// ----------------------------------------------------------------------
// 12. The mini‑project: A command‑line calculator using recursive descent
//    (The actual parsing functions are in calculator.cpp/.h)
// ----------------------------------------------------------------------
void run_calculator() {
    std::cout << "=== Recursive Descent Calculator ===\n";
    std::cout << "Enter expressions like: 2 + 3 * (4 - 1)\n";
    std::cout << "Type 'quit' to exit.\n";

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line) || line == "quit")
            break;

        try {
            double result = evaluate(line);
            std::cout << "= " << result << '\n';
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << '\n';
        }
    }
}

// ----------------------------------------------------------------------
// main – run demonstrations one by one, then the calculator
// ----------------------------------------------------------------------
int main() {
    std::cout << "C++ Foundation Educational Demo\n";
    std::cout << "===============================\n\n";

    demo_fundamental_types();
    demo_operators();
    demo_branching();
    demo_loops();
    demo_arrays_and_pointers();
    demo_c_strings();
    demo_structs();
    demo_functions();
    demo_scope_and_static();   // call it twice to see static variable
    demo_scope_and_static();
    demo_namespaces();
    demo_exceptions();

    // Optionally run the calculator at the end
    char choice;
    std::cout << "Run calculator? (y/n): ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (choice == 'y' || choice == 'Y')
        run_calculator();

    return 0;
}
