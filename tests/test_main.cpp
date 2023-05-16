//
// Created by eachu on 12/05/2023.
//
#include "../src/PythonCHelper.h"
#include "gtest/gtest.h"

using namespace mimic;

TEST(PythonCHelperTestCase, returnIntWithInput)
{
    PythonCHelper helper;

    helper.LoadScript("script_test");
    EXPECT_EQ(2, helper.executeFunction<int>("returnIntWithoutInput", "(si)", "hello", 42));
}

TEST(PythonCHelperTestCase, returnStringWithInput)
{
    PythonCHelper helper;
    helper.LoadScript("script_test");
    EXPECT_EQ("hello", helper.executeFunction<std::string>("returnStringWithoutInput", "(si)", "hello", 42));
}

TEST(PythonCHelperTestCase, testRunFunction)
{
    PythonCHelper helper;
    if(helper.LoadScript("script_test"))
    {
        EXPECT_EQ(true, helper.RunFunction("executeTest"));
    }
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}