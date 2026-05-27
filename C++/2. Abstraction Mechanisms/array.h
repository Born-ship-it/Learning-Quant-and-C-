// ======================================================================
// array.h
// 
// Fixed‑size array template with non‑type template parameter.
// Demonstrates non‑type parameters.
// ======================================================================

#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
#include <stdexcept>

template<typename T, std::size_t N>
class Array {
public:
    // Default constructor: value‑initializes elements
    Array() : data_{} {}

    // Element access
    T& operator[](std::size_t idx) {
        if (idx >= N) throw std::out_of_range("Array index out of range");
        return data_[idx];
    }
    const T& operator[](std::size_t idx) const {
        if (idx >= N) throw std::out_of_range("Array index out of range");
        return data_[idx];
    }

    std::size_t size() const noexcept { return N; }

    // Iterators (minimal)
    T* begin() noexcept { return data_; }
    const T* begin() const noexcept { return data_; }
    T* end() noexcept { return data_ + N; }
    const T* end() const noexcept { return data_ + N; }

private:
    T data_[N];
};

// Full specialization for Array<bool, 8> to store bits (demo only)
template<>
class Array<bool, 8> {
public:
    Array() : bits_(0) {}

    bool operator[](std::size_t idx) const {
        if (idx >= 8) throw std::out_of_range("Index out of range");
        return (bits_ >> idx) & 1;
    }
    // Non‑const reference not easily returned for a bit, so we use a proxy
    // (simplified here, not implemented for brevity)
    std::size_t size() const noexcept { return 8; }

private:
    unsigned char bits_;
};

#endif // ARRAY_H