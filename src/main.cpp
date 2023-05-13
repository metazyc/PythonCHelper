//
// Created by eachu on 13/05/2023.
//

#include "PythonCHelper.h"
using namespace mimic;

int main()
{
    PythonCHelper helper;
    if(helper.InitPythonEnv())
    {
        if(helper.LoadScript("script_test"))
        {
            helper.RunFunction("executeTest");
        }
    }
}