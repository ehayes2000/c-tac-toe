#ifndef MYVEC_H
#define MYVEC_H
#include <any>
#include <stdexcept>
#include <new>
#include <cstring>
#include <Python.h>

template <class T>
class MyVec
{
public:
    MyVec() : container_size(10), items(0), container(new T[10]){};
    ~MyVec();
    T &operator[](size_t);
    T pop();
    void append(T);
    size_t size();

private:
    size_t container_size;
    size_t items;
    T *container;
};

#endif
