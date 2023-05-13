//
// Created by eachu on 12/05/2023.
//

#include "PythonCHelper.h"
#define PY_SSIZE_T_CLEAN
#include "Python.h"

namespace mimic
{
    PythonCHelper::PythonCHelper()
    {

    }

    PythonCHelper::~PythonCHelper()
    {
        Py_Finalize();
    }

    bool PythonCHelper::InitPythonEnv() {
        Py_Initialize();

        if (!Py_IsInitialized())
        {
            PyErr_Print();
            return false;
        }
        return true;
    }

    bool PythonCHelper::LoadScript(const std::string &scriptName) {
        PyObject *pName;
        pName = PyUnicode_DecodeFSDefault(scriptName.c_str());
        script_object_ptr_ = PyImport_Import(pName);
        if (!script_object_ptr_)
        {
            PyErr_Print();
            return false;
        }
        Py_XDECREF(pName);
        return true;
    }

    bool PythonCHelper::RunFunction(const std::string &functionName) {
        PyObject * pFunc;
        if (script_object_ptr_ != nullptr)
        {
            pFunc = PyObject_GetAttrString(script_object_ptr_, functionName.c_str());
            if (pFunc && PyCallable_Check(pFunc))
            {
                PyObject *pValue = PyObject_CallObject(pFunc, nullptr);
                if (pValue != nullptr)
                {
                    Py_XDECREF(pValue);
                }
                else
                {
                    Py_XDECREF(pFunc);
                    Py_XDECREF(script_object_ptr_);
                    PyErr_Print();
                    return false;
                }
            }
            else
            {
                if (PyErr_Occurred())
                {
                    PyErr_Print();
                }
            }
            Py_XDECREF(pFunc);
            Py_XDECREF(script_object_ptr_);
            return true;
        }
        else
        {
            PyErr_Print();
            return false;
        }
    }

    PythonObject::PythonObject(PyObject* object_ptr):
    object_ptr_(object_ptr)
    {

    }

    PythonObject::~PythonObject()
    {

    }

}
