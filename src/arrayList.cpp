#include "arrayList.hpp"

ArrayList::ArrayList(){
    this->list = new py::object[SIZE];
    this->isInit = new bool[SIZE]();
    this->used = 0;
    this->size = SIZE;
}

// ArrayList::ArrayList(py::list &l){
//     this->size = l.size();
//     this->list = new py::handle[this->size];
//     this->isInit = new bool[this->size];
//     unsigned int j = 0;
//     for (auto i : l) {
//         this->list[j] = &i;
//         this->isInit[j++] = true;
//     }
// }
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

PYBIND11_MODULE(ArrayList, handler){
    py::class_<ArrayList>(handler, "ArrayList")
    .def(py::init<>())
    .def("__getitem__", &ArrayList::operator[])
    .def("__setitem__", &ArrayList::setitem);
}
