# 指定cmake最低版本
cmake_minimum_required(VERSION 3.23)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 创建一个变量，包含所有的测试源文件
set(TEST_SOURCES test_main.cpp)

add_executable(MainTest ${TEST_SOURCES})

target_link_libraries(MainTest PythonCHelper gtest)

#target_compile_features(MainTest PUBLIC cxx_std_14)

#target_include_directories(MainTest PRIVATE ${PROJECT_SOURCE_DIR}/tests)