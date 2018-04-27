#include <Python.h>

#include "curium.h"

static PyObject *curium_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    curium_hash((char *)PyBytes_AsString((PyObject*) input), (int)PyBytes_Size((PyObject*) input), output);
#else
    curium_hash((char *)PyString_AsString((PyObject*) input), (int)PyString_Size((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef CuriumMethods[] = {
    { "getPoWHash", curium_getpowhash, METH_VARARGS, "Returns the proof of work hash using curium hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef CuriumModule = {
    PyModuleDef_HEAD_INIT,
    "curium_hash",
    "...",
    -1,
    CuriumMethods
};

PyMODINIT_FUNC PyInit_curium_hash(void) {
    return PyModule_Create(&CuriumModule);
}

#else

PyMODINIT_FUNC initcurium_hash(void) {
    (void) Py_InitModule("curium_hash", CuriumMethods);
}
#endif
