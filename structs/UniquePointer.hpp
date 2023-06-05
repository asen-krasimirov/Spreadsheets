// From Georgi Terziev's repo
#pragma once

#include <utility>

template<typename T>
class UniquePointer{
private:
    T* ptr;

public:
    UniquePointer();
    UniquePointer(const UniquePointer<T>& ptr) = delete;
    UniquePointer& operator=(const UniquePointer<T>& ptr) = delete;
    UniquePointer(UniquePointer<T>&& other) noexcept;
    UniquePointer& operator=(UniquePointer<T>&& other) noexcept;
    ~UniquePointer();

    UniquePointer(T* ptr);

    T* operator->();
    const T* operator->() const;
    T& operator*();
    const T& operator*() const;

private:
    void move(UniquePointer<T>&& other) noexcept;
    void free();

};

template<typename T>
UniquePointer<T>::UniquePointer() {
    ptr = nullptr;
}

template<typename T>
UniquePointer<T>::UniquePointer(T* ptr) {
    this->ptr = ptr;
}

template<typename T>
UniquePointer<T>::UniquePointer(UniquePointer<T>&& other) noexcept {
    move(std::move(other));
}

template<typename T>
UniquePointer<T>& UniquePointer<T>::operator=(UniquePointer<T>&& other) noexcept {
    if (this != &other) {
        free();
        move(std::move(other));
    }

    return *this;
}

template<typename T>
T* UniquePointer<T>::operator->() {
    return ptr;
}

template<typename T>
const T* UniquePointer<T>::operator->() const {
    return ptr;
}

template<typename T>
T& UniquePointer<T>::operator*() {
    return *ptr;
}

template<typename T>
const T& UniquePointer<T>::operator*() const {
    return *ptr;
}

template<typename T>
UniquePointer<T>::~UniquePointer() {
    free();
}

template<typename T>
void UniquePointer<T>::move(UniquePointer<T>&& other) noexcept {
    ptr = other.ptr;
    other.ptr = nullptr;
}

template<typename T>
void UniquePointer<T>::free() {
    delete ptr;
}
