#include <pybind11/pybind11.h>

namespace py = pybind11;

class ArrayList{
public:
    ArrayList();
    py::object &operator [](unsigned long);
    ArrayList &operator *(unsigned long);
    ArrayList &operator +(ArrayList &);
    ArrayList &operator =(ArrayList &);
    ArrayList &setitem(unsigned long, py::object &);
    ArrayList &append(py::object &);
    ArrayList &remove(unsigned long);
    ArrayList &copy();
    unsigned long find(py::object &);

private:
    py::object *list;
    bool *isInit;
    unsigned long size;
    unsigned long used;
    void doubleArrayList();
};