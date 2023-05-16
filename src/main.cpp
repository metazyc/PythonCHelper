//
// Created by eachu on 13/05/2023.
//

#include "PythonCHelper.h"
using namespace mimic;

int main()
{
    PythonCHelper helper;

    helper.LoadScript("script_test");
    int result = helper.executeFunction<int>("returnIntWithoutInput", "(si)", "hello", 42);
    return result;
}