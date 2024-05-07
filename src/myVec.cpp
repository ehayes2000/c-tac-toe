#include "myVec.h"

template <class T>
T MyVec<T>::pop()
{
    if (items == 0)
        throw std::out_of_range("MyVec index out of range");
    return container[--items];
}

template <class T>
MyVec<T>::~MyVec()
{
    delete[] container;
}

template <class T>
T &MyVec<T>::operator[](size_t i)
{
    if (i >= items)
        throw std::out_of_range("MyVec index out of range");
    return container[i];
}

template <class T>
void MyVec<T>::append(T i)
{
    if (items == container_size)
    {
        size_t newSize = container_size * 2;
        T *newContainer = new T[newSize];
        std::memcpy(newContainer, container, sizeof(T) * items);
        delete[] container;
        container = newContainer;
        container_size = newSize;
    }
    container[items++] = i;
}

template <class T>
size_t MyVec<T>::size()
{
    return items;
}
// explicitly template for python objects to link python extension correctly
template class MyVec<PyObject *>;
