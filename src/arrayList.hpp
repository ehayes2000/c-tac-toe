#include <pybind11/pybind11.h>
#include <pybind11/operators.h>


namespace py = pybind11;

class ArrayList{
public:
    ArrayList();
    ArrayList(py::list&);
    ArrayList(ArrayList&);
    py::object *operator [](size_t);
    ArrayList &setitem(size_t, py::object &);
    ArrayList &append(py::object &);
    ArrayList &remove(size_t);
    ArrayList &copy();
    ArrayList &operator =(ArrayList &);
    ArrayList &operator *(size_t);
    ArrayList &operator +(ArrayList &);
    size_t find(py::object &);

private:
    py::object *list;
    bool *isInit;
    size_t size;
    size_t used;
    void doubleArrayList();
    const static int SIZE = 40;
};