//
// Created by eachu on 12/05/2023.
//
#include "../src/PythonCHelper.h"
#include "gtest/gtest.h"

using namespace mimic;

TEST(PythonCHelperTestCase, testInitPythonEnv)
{
    PythonCHelper helper;
    EXPECT_EQ(true, helper.InitPythonEnv());
}


TEST(PythonCHelperTestCase, testRunFunction)
{
    PythonCHelper helper;
    if(helper.InitPythonEnv())
    {
        if(helper.LoadScript("script_test"))
        {
            EXPECT_EQ(true, helper.RunFunction("executeTest"));
        }
    }
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}