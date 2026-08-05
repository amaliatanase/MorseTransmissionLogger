//
// Created by Anamaria Briciu on 24.03.2026.
//

#include "DynamicArray.h"

#include <iostream>
#include <stdexcept>

void DynamicArray::resize(unsigned int newSize) {
    if (newSize > this->capacity) {
        if (this->capacity == 0)
            this->capacity = 1;

        while (this->capacity < newSize) {
            this->capacity *= 2;
        }

        float *newElements = new float[this->capacity];
        std::copy(this->data, this->data + this->length, newElements);
        delete[] data;
        this->data = newElements;
    }

    if (newSize > this->length) {
        for (int i=this->length; i<newSize; i++) {
            this->data[i] = 0.0f;
        }
    }

    this->length = newSize;
}

DynamicArray::DynamicArray(const DynamicArray &other) {
    std::cout << "Copy constructor" << std::endl;

    this->length = other.length;
    this->capacity = other.capacity;

    float* newData = nullptr;
    if (this->capacity > 0) {
        newData = new float[this->capacity];
        for (int index = 0; index < this->length; ++index) {
            newData[index] = other.data[index];
        }
    }
    this->data = newData;
}

DynamicArray &DynamicArray::operator=(const DynamicArray &other) {
    std::cout << "operator=" << std::endl;
    if (this != &other) {
        this->capacity = other.capacity;
        this->length = other.length;

        delete[] this->data;
        float* newData = nullptr;
        if (other.capacity > 0) {
            newData = new float[this->capacity];
            for (unsigned i = 0; i < this->length; i++)
                newData[i] = other.data[i];
        }
        this->data = newData;
    }
    return *this;
}

//discussed at seminar towards the end (but we didn't change the
//implementation): maybe in this app, we would be better served
//by always allocating exactly as much memory as
//we need: start with length = capacity = 0,
//data = nullptr, and e.g. in computeSamples, call
//a method to allocate directly as much space as needed
//as opposed to starting with a given capacity,
//adding 1 element at a time + resizing when needed

//https://en.cppreference.com/w/cpp/error/out_of_range.html
float &DynamicArray::operator[](unsigned int index) {
    if (index >= this->length)
        throw std::out_of_range("DynamicArray operator[].");
    return this->data[index];
}

const float &DynamicArray::operator[](unsigned int index) const {
    if (index >= this->length)
        throw std::out_of_range("DynamicArray operator[].");
    return this->data[index];
}



DynamicArray::~DynamicArray() {
    std::cout<<"destructor"<<std::endl;
    delete[] this->data;
}

unsigned int DynamicArray::size() const {
    return this->length;
}

std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
    for (int i=0; i<arr.length; i++) {
        os << arr.data[i];
        if (i < arr.length - 1)
            os << " ";
    }
    return os;
}
