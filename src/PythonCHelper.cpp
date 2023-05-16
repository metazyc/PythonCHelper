//
// Created by eachu on 12/05/2023.
//

#include "PythonCHelper.h"
#define PY_SSIZE_T_CLEAN
namespace mimic
{

    PythonCHelper::PythonCHelper()
    {
        Py_Initialize();

        if (!Py_IsInitialized())
        {
            PyErr_Print();
            throw std::runtime_error("Failed to initialize Python environment");
        }
    }

    PythonCHelper::~PythonCHelper()
    {
        Py_Finalize();
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

    template <>
    int PythonCHelper::pythonToCpp<int>(PyObject* obj) {
        if(PyLong_Check(obj)) {
            return PyLong_AsLong(obj);
        }
        throw std::runtime_error("Object is not an integer");
    }

    template <>
    std::string PythonCHelper::pythonToCpp<std::string>(PyObject* obj) {
        if(PyUnicode_Check(obj)) {
            PyObject* temp_bytes = PyUnicode_AsEncodedString(obj, "UTF-8", "strict"); // New reference
            if(temp_bytes != NULL) {
                std::string str = PyBytes_AS_STRING(temp_bytes); // Borrowed pointer
                Py_DECREF(temp_bytes);
                return str;
            }
        }
        throw std::runtime_error("Object is not a string");
    }

    template <>
    std::map<std::string, PyObject*> PythonCHelper::pythonToCpp<std::map<std::string, PyObject*>>(PyObject* obj) {
        if(!PyDict_Check(obj)) {
            throw std::runtime_error("Object is not a dictionary");
        }

        std::map<std::string, PyObject*> result;
        PyObject *key, *value;
        Py_ssize_t pos = 0;

        while (PyDict_Next(obj, &pos, &key, &value)) {
            // convert Python string key to C++ string
            std::string key_str = pythonToCpp<std::string>(key);
            // add to result map
            result[key_str] = value;
        }

        return result;
    }
}
