// #include "myCoolCArray.h"
// #include <stdexcept>
// #include <string>

// template <class T>
// MyCoolCArray<T>::MyCoolCArray()
// {
//     container = new int[10];
//     size = 10;
//     items = 0;
// }

// template <class T>
// MyCoolCArray<T>::~MyCoolCArray()
// {
//     delete[] container;
// }

// template <class T>
// T MyCoolCArray<T>::operator[](size_t i)
// {
//     if (i < items)
//     {
//         return container[i];
//     }
//     throw std::out_of_range("ArrayList index out of range");
// }

// template <class T>
// T MyCoolCArray<T>::pop()
// {
//     if (items >= 1)
//     {
//         return container[--items];
//     }
//     throw std::out_of_range("ArrayList index out of range");
// }

// template <class T>
// void MyCoolCArray<T>::append(T i)
// {
//     if (items == size)
//     {
//         size *= 2;
//         int *new_container = new int[size];
//         std::memcpy(new_container, container, sizeof(int) * items);
//         delete[] container;
//         container = new_container;
//     }
//     container[items++] = i;
// }