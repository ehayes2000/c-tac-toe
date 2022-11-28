#include "arrayList.hpp"
#include <stdio.h>

ArrayList::ArrayList(){
    this->list = new py::object[SIZE];
    this->isInit = new bool[SIZE]();
    this->used = 0;
    this->size = SIZE;
}

ArrayList::ArrayList(py::iterable &l){
    printf("CREATE \n");
    this->size = py::len(l);
    this->list = new py::object[this->size];
    this->isInit = new bool[this->size];
    unsigned int j = 0;
    for (auto i : l) {
        this->list[j] = py::reinterpret_borrow<py::object>(i);
        this->isInit[j++] = true;
    }
}

ArrayList::~ArrayList(){
    printf("DESTROY %p \n", this->list);

    // delete this->list;
    // delete this->isInit;
}

py::object *ArrayList::operator [](size_t i){
    if (i >= size)
        throw std::out_of_range ("List index out of range");
    if (!this->isInit[i])
        return nullptr;
    return &this->list[i];
}

ArrayList &ArrayList::setitem(size_t i, py::object &o){
    if (i >= size)
        throw std::out_of_range ("List index out of range");
    this->isInit[i] = true;
    this->list[i] = o;
    return *this;
}

std::string ArrayList::toString() const {
    printf("MEM REF: %p \n", this->list);
    std::string s = "[";
    for (size_t i = 0; i < this->size; i ++){
        s += py::str(this->list[i]);
        if (i != this->size - 1)
            s += ", ";        
    }
    s += "]";
    return s;
}





PYBIND11_MODULE(ArrayList, handler){
    py::class_<ArrayList>(handler, "ArrayList")
    .def(py::init<py::iterable&>())
    .def(py::init<>())
    .def("__str__", &ArrayList::toString)
    .def("__repr__", &ArrayList::toString)
    .def("__getitem__", &ArrayList::operator[])
    .def("__setitem__", &ArrayList::setitem);
}
