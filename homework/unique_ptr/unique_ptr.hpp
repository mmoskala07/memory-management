#pragma once

namespace my {

template <typename T>
class unique_ptr {
private:
    T* ptr;

public:
    // Constructor
    unique_ptr(T* p = nullptr) {
        ptr = p;
    }
    // Copy constructor
    unique_ptr(unique_ptr& other) = delete;
    // Move constructor
    unique_ptr(unique_ptr&& other) {
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    // Copy assignment
    unique_ptr& operator=(unique_ptr& other) = delete;
    // Move assignment
    unique_ptr& operator=(unique_ptr&& other) {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    // Destructor
    ~unique_ptr() {
        delete ptr;
    }

    T& operator*() {
        return *ptr;
    }
    T* operator->() {
        return ptr;
    }
    T* get() {
        return ptr;
    }
    T* release() {
        T* temp_ptr = ptr;
        ptr = nullptr;
        return temp_ptr;
    }
    void reset(T* new_obj = nullptr) {
        delete ptr;
        ptr = new_obj;
    }
};

}  // namespace my
