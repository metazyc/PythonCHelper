//
// Created by eachu on 12/05/2023.
//
#include <string>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include "Python.h"
#include <map>
#include <vector>

#ifndef PYTHONCHELPER_PYTHONCHELPER_H
#define PYTHONCHELPER_PYTHONCHELPER_H

namespace mimic
{
    class PythonCHelper
    {
    public:
        PythonCHelper();
        ~PythonCHelper();
        bool LoadScript(const std::string& scriptName);
        //run function, dont care the return
        bool RunFunction(const std::string& functionName);

        template <typename T, typename... Args>
        T executeFunction(const std::string& functionName, const char* format, Args&&... args) {
            PyObject* pFunc = PyObject_GetAttrString(script_object_ptr_, functionName.c_str());
            if (pFunc && PyCallable_Check(pFunc)) {
                PyObject* pArgs = buildValue(format, std::forward<Args>(args)...);
                PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
                Py_XDECREF(pArgs);
                if (pValue != nullptr) {
                    T result = pythonToCpp<T>(pValue);
                    Py_DECREF(pValue);
                    return result;
                }
            }
            throw std::runtime_error("Failed to execute function");

        }
    private:

        template <typename T>
        T pythonToCpp(PyObject* obj);

        template <typename... Args>
        PyObject* buildValue(const char* format, Args&&... args) {
            return Py_BuildValue(format, std::forward<Args>(args)...);
        }


        template <typename T>
        std::vector<T> pythonToCppList(PyObject* obj) {
            if(!PyList_Check(obj)) {
                throw std::runtime_error("Object is not a list");
            }

            std::vector<T> result;
            Py_ssize_t size = PyList_Size(obj);

            for(Py_ssize_t i = 0; i < size; i++) {
                // get the i-th item in the list
                PyObject* item = PyList_GetItem(obj, i);
                // convert the item to a C++ object of type T
                T value = pythonToCpp<T>(item);
                // add to result vector
                result.push_back(value);
            }

            return result;
        }
    private:
        PyObject* script_object_ptr_= nullptr;

    };

}

#endif //PYTHONCHELPER_PYTHONCHELPER_H
