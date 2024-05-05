#define PY_SSIZE_T_CLEAN
#include <stdexcept>
#include <Python.h>
#include "myCoolCArray.h"

typedef struct
{
    PyObject_HEAD
        MyCoolCArray<PyObject *> *obj;
} PyCoolCArray;

static int MyCoolCArray_init(PyCoolCArray *self, PyObject *args, PyObject *kwds)
{
    self->obj = new MyCoolCArray<PyObject *>();
    if (!self->obj)
    {
        PyErr_SetString(PyExc_MemoryError, "Could not allocate ArrayList object");
        return -1;
    }
    return 0;
}

static void MyCoolCArray_dealloc(PyCoolCArray *self)
{
    delete self->obj;
    PyObject_GC_UnTrack(self);
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *MyCoolCArray_append(PyCoolCArray *self, PyObject *value)
{
    Py_INCREF(value);
    self->obj->append(value);
    Py_RETURN_NONE;
}

static PyObject *MyCoolCArray_pop(PyCoolCArray *self)
{
    try
    {
        PyObject *popped = self->obj->pop();
        return popped;
    }
    catch (std::out_of_range)
    {
        PyErr_SetString(PyExc_IndexError, "pop from empty ArrayList");
        return NULL;
    }
}

static PyMethodDef PyArrayList_methods[] = {
    {"pop", (PyCFunction)MyCoolCArray_pop, METH_NOARGS,
     "Remove and return last integer from ArrayList"},
    {"append", (PyCFunction)MyCoolCArray_append, METH_O,
     "Append an integer to ArrayList"},
    {NULL}};

static PyTypeObject PyCoolCArrayType = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
                   .tp_name = "myCoolCArray.MyCoolCArray",
    .tp_doc = PyDoc_STR("Resizable array"),
    .tp_basicsize = sizeof(PyCoolCArray),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)MyCoolCArray_init,
    .tp_dealloc = (destructor)MyCoolCArray_dealloc,
    .tp_methods = PyArrayList_methods,
};

static PyModuleDef arrayListModule = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "myCoolCArray",
    .m_doc = "An exploration of c types in python",
    .m_size = -1,
};

PyMODINIT_FUNC PyInit_MyCoolCArray(void)
{
    PyObject *m;
    if (PyType_Ready(&PyCoolCArrayType) < 0)
        return NULL;
    m = PyModule_Create(&arrayListModule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&PyCoolCArrayType);
    if (PyModule_AddObject(m, "myCoolCArray", (PyObject *)&PyCoolCArrayType) < 0)
    {
        Py_DECREF(&PyCoolCArrayType);
        Py_DECREF(m);
    }
    return m;
}
