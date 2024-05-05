#include "arrayList.h"
#include <stdexcept>
#include <string>

ArrayList::ArrayList()
{
    container = new int[10];
    size = 10;
    items = 0;
}

int ArrayList::operator[](size_t i)
{
    if (i < items)
    {
        return container[i];
    }
    throw std::out_of_range("ArrayList index out of range");
}

int ArrayList::pop()
{
    if (items >= 1)
    {
        return container[--items];
    }
    throw std::out_of_range("ArrayList index out of range");
}

void ArrayList::append(int i)
{
    if (items == size)
    {
        size *= 2;
        int *new_container = new int[size];
        std::memcpy(new_container, container, sizeof(int) * items);
        delete[] container;
        container = new_container;
    }
    container[items++] = i;
}