//
// Created by eachu on 12/05/2023.
//
#include <string>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include "Python.h"

#ifndef PYTHONCHELPER_PYTHONCHELPER_H
#define PYTHONCHELPER_PYTHONCHELPER_H

namespace mimic
{

    class PythonCHelper
    {
    public:
        PythonCHelper();
        ~PythonCHelper();
        bool InitPythonEnv();
        bool LoadScript(const std::string& scriptName);
        bool RunFunction(const std::string& functionName);
    private:

    private:
        PyObject* script_object_ptr_= nullptr;

    };



    class PythonObject
    {
    public:
        PythonObject(PyObject* object_ptr = nullptr);
        ~PythonObject();
    private:
        PyObject* object_ptr_=nullptr;
    };


}

#endif //PYTHONCHELPER_PYTHONCHELPER_H
