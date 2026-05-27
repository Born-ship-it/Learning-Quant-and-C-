// ======================================================================
// stack.h
// 
// Stack template using Vector<T> as underlying storage (composition).
// ======================================================================

#ifndef STACK_H
#define STACK_H

#include "vector.h"

template<typename T>
class Stack {
public:
    void push(const T& value) { data_.push_back(value); }
    void pop() { data_.pop_back(); }
    T& top() { return data_.back(); }
    const T& top() const { return data_.back(); }
    bool empty() const { return data_.size() == 0; }
    std::size_t size() const { return data_.size(); }
private:
    Vector<T> data_;
};

#endif // STACK_H