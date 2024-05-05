#define PY_SSIZE_T_CLEAN
#include <stdexcept>
#include <Python.h>
#include "arrayList.h"

typedef struct
{
    PyObject_HEAD
        ArrayList *obj;
} PyArrayList;

static int ArrayList_init(PyArrayList *self, PyObject *args, PyObject *kwds)
{
    self->obj = new ArrayList();
    if (!self->obj)
    {
        PyErr_SetString(PyExc_MemoryError, "Could not allocate ArrayList object");
        return -1;
    }
    return 0;
}

static void ArrayList_dealloc(PyArrayList *self)
{
    delete self->obj;
    PyObject_GC_UnTrack(self);
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *ArrayList_append(PyArrayList *self, PyObject *value)
{
    if (!PyLong_Check(value))
    {
        PyErr_SetString(PyExc_TypeError, "Appended value must be an integer");
        return NULL;
    }
    int int_val = (int)PyLong_AsLong(value);
    self->obj->append(int_val);
    Py_RETURN_NONE;
}

static PyObject *ArrayList_pop(PyArrayList *self)
{
    try
    {
        int val = self->obj->pop();
        return PyLong_FromLong(val);
    }
    catch (std::out_of_range)
    {
        PyErr_SetString(PyExc_IndexError, "pop from empty ArrayList");
        return NULL;
    }
}

static PyMethodDef PyArrayList_methods[] = {
    {"append", (PyCFunction)ArrayList_append, METH_O,
     "Append an integer to ArrayList"},
    {"pop", (PyCFunction)ArrayList_pop, METH_NOARGS,
     "Remove and return last integer from ArrayList"},
    {"p"} {NULL}};

static PyTypeObject PyArrayListType = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0).tp_name = "arrayList.ArrayList",
    .tp_doc = PyDoc_STR("Resizable array"),
    .tp_basicsize = sizeof(ArrayList),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)ArrayList_init,
    .tp_methods = PyArrayList_methods,
};

static PyModuleDef arrayListModule = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "arrayList",
    .m_doc = "An exploration of c types in python",
    .m_size = -1,
};

PyMODINIT_FUNC PyInit_ArrayList(void)
{
    PyObject *m;
    if (PyType_Ready(&PyArrayListType) < 0)
        return NULL;
    m = PyModule_Create(&arrayListModule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&PyArrayListType);
    if (PyModule_AddObject(m, "ArrayList", (PyObject *)&PyArrayListType) < 0)
    {
        Py_DECREF(&PyArrayListType);
        Py_DECREF(m);
    }
    return m;
}
