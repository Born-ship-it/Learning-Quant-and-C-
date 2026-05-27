// ======================================================================
// demo_templates.h / demo_templates.cpp
// 
// Function templates for generic algorithms:
// - max (two values)
// - swap (two variables)
// - find (iterator-based)
// Also demonstrates explicit instantiation and specialization.
// ======================================================================

#ifndef DEMO_TEMPLATES_H
#define DEMO_TEMPLATES_H

#include <iostream>
#include <cstring>

// Generic max
template<typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

// Generic swap
template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// Generic find: returns iterator to first match, or last if not found
template<typename Iterator, typename T>
Iterator find(Iterator first, Iterator last, const T& value) {
    while (first != last) {
        if (*first == value)
            return first;
        ++first;
    }
    return last;
}

// Full specialization of max for const char* (C‑strings)
template<>
const char* max(const char* a, const char* b) {
    return (std::strcmp(a, b) > 0) ? a : b;
}

// Explicit instantiation declarations (if needed)
// extern template int max<int>(int, int);  // optional

#endif // DEMO_TEMPLATES_H