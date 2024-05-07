#ifndef PYVEC_H
#define PYVEC_H

#include <Python.h>
#include "myVec.h"

typedef struct
{
    PyObject_HEAD
        MyVec<PyObject *> *obj;
} PyVec;

typedef struct
{
    PyObject_HEAD
        PyVec *array;
    size_t position;
} PyIterator;

static int MyVec_init(PyVec *self, PyObject *args, PyObject *kwds);
static void MyVec_dealloc(PyVec *self);
static PyObject *MyVec_append(PyVec *self, PyObject *value);
static PyObject *MyVec_pop(PyVec *self);
static PyObject *MyVec_richcompare(PyObject *a, PyObject *b, int op);
static PyObject *MyVec_iter(PyObject *self);
static int MyVec_setitem(PyObject *self, PyObject *key, PyObject *value);
static Py_ssize_t MyVec_length(PyVec *self);
static PyObject *MyVec_getitem(PyObject *self, PyObject *key);

static PyObject *PyIterator_iter(PyObject *self);
static PyObject *PyIterator_next(PyObject *self);
static void PyIterator_dealloc(PyIterator *self);

static PyTypeObject PyIteratorType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "PyIterator",
    .tp_doc = "Iterator for PyVec",
    .tp_basicsize = sizeof(PyIterator),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_iter = PyIterator_iter,
    .tp_iternext = PyIterator_next,
    .tp_dealloc = (destructor)PyIterator_dealloc,
    .tp_new = PyType_GenericNew,
};
static PyMethodDef PyVec_methods[] = {
    {"pop", (PyCFunction)MyVec_pop, METH_NOARGS,
     "Remove and return last integer from MyVec"},
    {"append", (PyCFunction)MyVec_append, METH_O,
     "Append an integer to MyVec"},
    {NULL}};

static PySequenceMethods MyVec_sequence_methods = {
    .sq_length = (lenfunc)MyVec_length,
};

static PyMappingMethods MyVec_mapping_methods = {
    .mp_length = NULL,
    .mp_subscript = MyVec_getitem,
    .mp_ass_subscript = MyVec_setitem,
};

static PyTypeObject PyVecType = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
                   .tp_name = "myVec.MyVec",
    .tp_doc = PyDoc_STR("Resizable array"),
    .tp_basicsize = sizeof(PyVec),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)MyVec_init,
    .tp_iter = MyVec_iter,
    .tp_dealloc = (destructor)MyVec_dealloc,
    .tp_richcompare = MyVec_richcompare,
    .tp_as_mapping = &MyVec_mapping_methods,
    .tp_methods = PyVec_methods,
    .tp_as_sequence = &MyVec_sequence_methods,
};

static PyModuleDef myVecModule = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "myVec",
    .m_doc = "An exploration of c types in python",
    .m_size = -1,
};

PyMODINIT_FUNC PyInit_myVec(void)
{
    PyObject *m;
    if (PyType_Ready(&PyVecType) < 0)
        return NULL;
    m = PyModule_Create(&myVecModule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&PyVecType);
    if (PyModule_AddObject(m, "MyVec", (PyObject *)&PyVecType) < 0)
    {
        Py_DECREF(&PyVecType);
        Py_DECREF(m);
    }
    return m;
}
#endif