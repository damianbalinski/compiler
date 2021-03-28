#include <Python.h>
#include "arithmetic.c"

// zero
static PyObject * pzero(PyObject * self, PyObject * args)
{
    int x;
    if (!PyArg_ParseTuple(args, "i", &x)) return NULL;
    return Py_BuildValue("i", _zero(x));
}

// one
static PyObject * pone(PyObject * self, PyObject * args)
{
    int x;
    if (!PyArg_ParseTuple(args, "i", &x)) return NULL;
    return Py_BuildValue("i", _one(x));
}

// norm
static PyObject * pnorm(PyObject * self, PyObject * args)
{
    long long x;
    if (!PyArg_ParseTuple(args, "L", &x)) return NULL;
    return Py_BuildValue("i", _norm(x));
}

// norm_pow
static PyObject * pnorm_pow(PyObject * self, PyObject * args)
{
    long long x;
    if (!PyArg_ParseTuple(args, "L", &x)) return NULL;
    return Py_BuildValue("i", _norm_pow(x));
}

// add
static PyObject * padd(PyObject * self, PyObject * args)
{
    int x, y;
    if (!PyArg_ParseTuple(args, "ii", &x, &y)) return NULL;
    return Py_BuildValue("i", _add(x, y));
}

// sub
static PyObject * psub(PyObject * self, PyObject * args)
{
    int x, y;
    if (!PyArg_ParseTuple(args, "ii", &x, &y)) return NULL;
    return Py_BuildValue("i", _sub(x, y));
}

// mul
static PyObject * pmul(PyObject * self, PyObject * args)
{
    int x, y;
    if (!PyArg_ParseTuple(args, "ii", &x, &y)) return NULL;
    return Py_BuildValue("i", _mul(x, y));
}

// div
static PyObject * pdiv(PyObject * self, PyObject * args)
{
    int x, y;
    if (!PyArg_ParseTuple(args, "ii", &x, &y)) return NULL;
    return Py_BuildValue("i", _div(x, y));
}

// pow
static PyObject * ppow(PyObject * self, PyObject * args)
{
    int x, y;
    if (!PyArg_ParseTuple(args, "ii", &x, &y)) return NULL;
    return Py_BuildValue("i", _pow(x, y));
}

static PyMethodDef myMethods[] = {
    {"pzero",     pzero,     METH_VARARGS, "Sprawdza czy zero."},
    {"pone",      pone,      METH_VARARGS, "Sprawdza czy jeden."},
    {"pnorm",     pnorm,     METH_VARARGS, "Normalizacja."},
    {"pnorm_pow", pnorm_pow, METH_VARARGS, "Normalizacja wykladnika."},
    {"padd",      padd,      METH_VARARGS, "Dodawanie."},
    {"psub",      psub,      METH_VARARGS, "Odejmowanie."},
    {"pmul",      pmul,      METH_VARARGS, "Mnozenie."},
    {"pdiv",      pdiv,      METH_VARARGS, "Dzielenie."},
    {"ppow",      ppow,      METH_VARARGS, "Potegowanie."},
    {NULL,        NULL,      0,            NULL}
};

static struct PyModuleDef myModule = {
    PyModuleDef_HEAD_INIT,
    "myarythmetic",
    "mymodule",
    -1,
    myMethods
};

PyMODINIT_FUNC PyInit_myarithmetic(void)
{
    return PyModule_Create( &myModule);
}