#define PY_SSIZE_T_CLEAN
#include <stdexcept>
#include <Python.h>
#include "myVecModule.h"

static int MyVec_init(PyVec *self, PyObject *args, PyObject *kwds)
{
    self->obj = new MyVec<PyObject *>();
    PyObject *inputObject = NULL;
    if (!PyArg_ParseTuple(args, "|O:__init__", &inputObject))
        return -1;

    if (!self->obj)
    {
        PyErr_SetString(PyExc_MemoryError, "Could not allocate MyVec object");
        return -1;
    }
    if (!inputObject)
    {
        return 0;
    }

    PyObject *iterator = PyObject_GetIter(inputObject);
    if (iterator)
    {
        PyObject *item;
        while ((item = PyIter_Next(iterator)) != NULL)
        {
            self->obj->append(item);
            Py_INCREF(item);
        }
        Py_DECREF(iterator);
        if (PyErr_Occurred())
        {
            PyErr_Print();
            delete self->obj;
            return -1;
        }
    }
    else
    {
        PyErr_Clear();
        Py_INCREF(inputObject);
        self->obj->append(inputObject);
    }

    return 0;
}

static void MyVec_dealloc(PyVec *self)
{
    size_t size = self->obj->size();
    for (size_t i = 0; i < size; i++)
    {
        PyObject *item = (*self->obj)[i];
        Py_XDECREF(item);
    }
    delete self->obj;
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *MyVec_append(PyVec *self, PyObject *value)
{
    Py_INCREF(value);
    self->obj->append(value);
    Py_RETURN_NONE;
}

static PyObject *MyVec_pop(PyVec *self)
{
    try
    {
        PyObject *popped = self->obj->pop();
        return popped;
    }
    catch (std::out_of_range)
    {
        PyErr_SetString(PyExc_IndexError, "pop from empty MyVec");
        return NULL;
    }
}
static PyObject *MyVec_richcompare(PyObject *a, PyObject *b, int op)
{
    PyVec *array_a = (PyVec *)a;
    PyVec *array_b = (PyVec *)b;
    if (op == Py_EQ)
    {
        if (array_a->obj->size() != array_b->obj->size())
        {
            Py_RETURN_FALSE;
        }
        for (size_t i = 0; i < array_a->obj->size(); i++)
        {
            PyObject *item_a = (*array_a->obj)[i];
            PyObject *item_b = (*array_b->obj)[i];
            int result = PyObject_RichCompareBool(item_a, item_b, Py_EQ);
            if (result != 1)
            {
                if (result < 0)
                {
                    return NULL;
                }
                Py_RETURN_FALSE;
            }
        }
        Py_RETURN_TRUE;
    }

    Py_RETURN_NOTIMPLEMENTED;
}

static PyObject *PyIterator_iter(PyObject *self)
{
    Py_INCREF(self);
    return self;
}

static PyObject *PyIterator_next(PyObject *self)
{
    PyIterator *iterator = (PyIterator *)self;

    if (iterator->position >= iterator->array->obj->size())
    {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }

    PyObject *item = (*(iterator->array->obj))[iterator->position++];
    Py_INCREF(item);
    return item;
}
static void PyIterator_dealloc(PyIterator *self)
{
    Py_XDECREF(self->array);
    PyObject_Del(self);
}
static PyObject *MyVec_iter(PyObject *self)
{
    PyIterator *iterator = PyObject_New(PyIterator, &PyIteratorType);
    if (iterator == NULL)
        return NULL;

    Py_INCREF(self);
    iterator->array = (PyVec *)self;
    iterator->position = 0;
    return (PyObject *)iterator;
}

static int MyVec_setitem(PyObject *self, PyObject *key, PyObject *value)
{
    if (!PyLong_Check(key))
    {
        PyErr_SetString(PyExc_TypeError, "Index must be an integer");
        return 0;
    }
    unsigned long index = PyLong_AsLong(key);
    if (value == NULL)
    {
        PyErr_SetString(PyExc_TypeError, "Cannot delete item");
        return -1;
    }
    PyVec *array = (PyVec *)self;
    if (index < 0 || index >= array->obj->size())
    {
        PyErr_SetString(PyExc_IndexError, "index out of range");
        return -1;
    }
    Py_INCREF(value);
    PyObject *old_item = (*(array->obj))[index];
    Py_DECREF(old_item);
    (*(array->obj))[index] = value;
    return 0;
}

static PyObject *MyVec_getitem(PyObject *self, PyObject *key)
{
    if (!PyLong_Check(key))
    {
        PyErr_SetString(PyExc_TypeError, "Index must be an integer");
        return NULL;
    }
    long index = PyLong_AsLong(key);
    PyVec *array = (PyVec *)self;
    PyObject *item = nullptr;
    try
    {
        item = (*array->obj)[index];
    }
    catch (std::out_of_range)
    {
        PyErr_SetString(PyExc_IndexError, "index out of range");
        return NULL;
    }
    Py_INCREF(item);
    return item;
}

static Py_ssize_t MyVec_length(PyVec *self)
{
    return self->obj->size();
}