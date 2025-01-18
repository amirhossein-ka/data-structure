#pragma once
#include <cstddef> // for size_t
#include <iostream>
#include <stdexcept>


template<typename T>
class Stack {
public:
    explicit Stack(const size_t max_size): max_size(max_size), current_size(0), data(new T[max_size]) {
        if (max_size < 1) {
            throw std::invalid_argument("Stack size must be greater than 0");
        }
    }

    ~Stack() {
        delete[] data;
    }

    void push(T &value) {
        if (current_size == max_size) {
            throw std::length_error("Stack size is greater than max_size");
        }
        data[current_size++] = value;
    }

    T *pop() {
        if (current_size == 0) {
            throw std::length_error("Stack is empty");
        }
        return &data[--current_size];
    }

    T *peek() const {
        if (current_size == 0) {
            throw std::length_error("Stack is empty");
        }
        return &data[current_size];
    }

    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, const Stack<U> &stack)  {
        for (size_t i = 0; i < stack.current_size; i++) {
            os << stack.data[i] << " ";
        }
        return os;
    }

private:
    size_t max_size;
    size_t current_size;
    T *data;
};
