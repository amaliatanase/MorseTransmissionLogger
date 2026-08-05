//
// Created by Anamaria Briciu on 24.03.2026.
//

#ifndef SEMINAR3_1011_DYNAMICARRAY_H
#define SEMINAR3_1011_DYNAMICARRAY_H
#include <iostream>


class DynamicArray {
private:
    //TO-DO: change to start from nullptr, capacity = 0, size = 0
    float *data = nullptr;
    //we could also use size_t instead of unsigned_int
    unsigned int length = 0;
    unsigned int capacity = 0;

public:
    DynamicArray() = default;

    //if we change to start from capacity =0, check that other.capacity
    //is different from 0, and only then copy from other array
    //i.e. avoid new float[0]
    DynamicArray(const DynamicArray &other);

    //if we change to start from capacity =0, check that other.capacity
    //is different from 0, and only then copy from other array
    //i.e. avoid new float[0]
    DynamicArray &operator=(const DynamicArray &other);

    ~DynamicArray();

    //TO-DO: replace the adding logic with
    //resize logic, where:
    //void resize(int newSize) is a public method that
    //      -> if newSize greater than previous capacity,
    //         newCapacity is obtained by doubling the previous capacity until
    //         we obtain a number greater or equal to newSize
    //      -> previous data is copied in new array with newCapacity (can
    //         be implemented in separate function)
    //      -> if newSize is greater than previous size (=length), 0.0f is placed at each position
    //         from previous length to newSize
    //      -> new length is equal to newSize
    void resize(unsigned int newSize);

    //void add(float e);

    float &operator[](unsigned int index);

    const float &operator[](unsigned int index) const;


    unsigned int size() const;

    friend std::ostream &operator<<(std::ostream &os, const DynamicArray &arr);
};


#endif //SEMINAR3_1011_DYNAMICARRAY_H
