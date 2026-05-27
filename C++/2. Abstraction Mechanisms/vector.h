// ======================================================================
// vector.h
//
// A simple dynamic array (RAII class) demonstrating:
// - Resource management (new/delete[])
// - Copy constructor, copy assignment, destructor
// - Exception‑safe copy assignment using copy‑and‑swap
// - Move semantics (optional, shown)
// - const member functions, operator[]
// - Exception safety: strong guarantee for assignment
// ======================================================================

#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm> // std::copy, std::swap
#include <stdexcept>
#include <cstddef>

template<typename T>
class Vector {
public:
// Constructors
Vector() : data_(nullptr), size_(0), capacity_(0) {}

explicit Vector(std::size_t count, const T& value = T())
: size_(count), capacity_(count)
{
data_ = new T[capacity_];
for (std::size_t i = 0; i < size_; ++i)
data_[i] = value;
}

// Copy constructor
Vector(const Vector& other)
: size_(other.size_), capacity_(other.size_)
{
data_ = new T[capacity_];
std::copy(other.data_, other.data_ + size_, data_);
}

// Copy assignment (strong exception guarantee via copy‑and‑swap)
Vector& operator=(const Vector& rhs) {
Vector temp(rhs); // may throw, but *this is unchanged
swap(temp);
return *this;
}

// Move constructor
Vector(Vector&& other) noexcept
: data_(other.data_), size_(other.size_), capacity_(other.capacity_)
{
other.data_ = nullptr;
other.size_ = other.capacity_ = 0;
}

// Move assignment
Vector& operator=(Vector&& other) noexcept {
if (this != &other) {
delete[] data_;
data_ = other.data_;
size_ = other.size_;
capacity_ = other.capacity_;
other.data_ = nullptr;
other.size_ = other.capacity_ = 0;
}
return *this;
}

~Vector() { delete[] data_; }

// Element access
T& operator[](std::size_t idx) {
if (idx >= size_) throw std::out_of_range("Vector index out of range");
return data_[idx];
}
const T& operator[](std::size_t idx) const {
if (idx >= size_) throw std::out_of_range("Vector index out of range");
return data_[idx];
}

std::size_t size() const noexcept { return size_; }
std::size_t capacity() const noexcept { return capacity_; }

void push_back(const T& value) {
if (size_ == capacity_) {
reserve(capacity_ == 0 ? 1 : capacity_ * 2);
}
data_[size_++] = value;
}

void pop_back() {
if (size_ == 0) throw std::underflow_error("pop_back on empty Vector");
--size_;
// optional: call destructor on last element (for non-trivial types)
data_[size_].~T();
}

void reserve(std::size_t new_cap) {
if (new_cap <= capacity_) return;
T* new_data = new T[new_cap];
std::copy(data_, data_ + size_, new_data);
delete[] data_;
data_ = new_data;
capacity_ = new_cap;
}

void swap(Vector& other) noexcept {
using std::swap;
swap(data_, other.data_);
swap(size_, other.size_);
swap(capacity_, other.capacity_);
}

T& back() {
if (size_ == 0) throw std::out_of_range("back on empty Vector");
return data_[size_ - 1];
}
const T& back() const {
if (size_ == 0) throw std::out_of_range("back on empty Vector");
return data_[size_ - 1];
}

private:
T* data_;
std::size_t size_;
std::size_t capacity_;
};

template<typename T>
void swap(Vector<T>& a, Vector<T>& b) noexcept {
a.swap(b);
}

#endif // VECTOR_H