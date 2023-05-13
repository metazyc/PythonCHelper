cmake_minimum_required(VERSION 3.23)
project(PythonCHelper VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(PythonCHelper SHARED ./src/PythonCHelper.h ./src/PythonCHelper.cpp)

add_subdirectory(${PROJECT_SOURCE_DIR}/library/googletest-1.13.0)
add_subdirectory(tests)

#set(PYTHON_LIBRARY "${PROJECT_SOURCE_DIR}/library/Python311/libs/python3.lib")
#set(PYTHON_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/library/Python311/include")

find_package(PythonLibs REQUIRED)
target_include_directories(PythonCHelper PRIVATE ${PYTHON_INCLUDE_DIR})
target_link_libraries(PythonCHelper ${PYTHON_LIBRARY})

target_include_directories(MainTest PRIVATE ${PROJECT_SOURCE_DIR}/tests ${PYTHON_INCLUDE_DIR})
target_link_libraries(MainTest ${PYTHON_LIBRARY})

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(Main ${PROJECT_SOURCE_DIR}/src/main.cpp)

target_link_libraries(Main PRIVATE PythonCHelper)

add_custom_command(TARGET PythonCHelper POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:PythonCHelper>
        ${CMAKE_CURRENT_BINARY_DIR}/tests)

add_custom_command(TARGET PythonCHelper PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/script_test.py
        ${CMAKE_CURRENT_BINARY_DIR}/script_test.py)

add_custom_command(TARGET PythonCHelper PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/script_test.py
        ${CMAKE_CURRENT_BINARY_DIR}/tests/script_test.py)
file(GLOB DLL_FILES "${PYTHON_LIBRARY}/*.dll")

foreach(DLL_FILE ${DLL_FILES})
    add_custom_command(TARGET PythonCHelper POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${DLL_FILE}
            ${CMAKE_CURRENT_BINARY_DIR}/tests)
endforeach()
