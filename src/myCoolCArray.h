#ifndef MYCOOLCARRAY_H
#define MYCOOLCARRAY_H
#include <any>
#include <stdexcept>
#include <new>
#include <cstring>

template <class T>
class MyCoolCArray
{
public:
    MyCoolCArray() : size(10), items(0), container(new T[10]) {}

    ~MyCoolCArray()
    {
        delete[] container;
    }

    T &operator[](size_t i)
    {
        if (i >= items)
            throw std::out_of_range("ArrayList index out of range");
        return container[i];
    }

    T pop()
    {
        if (items == 0)
            throw std::out_of_range("ArrayList index out of range");
        return container[--items];
    }

    void append(T i)
    {
        if (items == size)
        {
            size_t newSize = size * 2;
            T *newContainer = new T[newSize];
            std::memcpy(newContainer, container, sizeof(T) * items);
            delete[] container;
            container = newContainer;
            size = newSize;
        }
        container[items++] = i;
    }

private:
    size_t size;
    size_t items;
    T *container;
};

#endif // MYCOOLCARRAY_H
