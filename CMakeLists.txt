cmake_minimum_required(VERSION 3.23)
project(PythonCHelper VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(PythonCHelper SHARED ./src/PythonCHelper.h ./src/PythonCHelper.cpp)

add_subdirectory(${PROJECT_SOURCE_DIR}/library/googletest)
add_subdirectory(tests)

#set(PYTHON_LIBRARY "${PROJECT_SOURCE_DIR}/library/Python311/libs/python3.lib")
#set(PYTHON_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/library/Python311/include")

find_package(Python COMPONENTS Interpreter Development REQUIRED)

message(STATUS "Python include dirs: ${Python_INCLUDE_DIRS}")

target_include_directories(PythonCHelper PRIVATE ${Python_INCLUDE_DIRS})
target_link_libraries(PythonCHelper ${Python_LIBRARIES})

target_include_directories(MainTest PRIVATE ${PROJECT_SOURCE_DIR}/tests ${Python_INCLUDE_DIRS})
target_link_libraries(MainTest ${Python_LIBRARIES})

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(Main ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_include_directories(Main PRIVATE ${Python_INCLUDE_DIRS})
target_link_libraries(Main PythonCHelper ${Python_LIBRARIES})

add_custom_command(TARGET PythonCHelper POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:PythonCHelper>
        ${CMAKE_CURRENT_BINARY_DIR}/tests)

add_custom_command(TARGET PythonCHelper POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/script_test.py
        ${CMAKE_CURRENT_BINARY_DIR}/script_test.py)

add_custom_command(TARGET PythonCHelper POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/script_test.py
        ${CMAKE_CURRENT_BINARY_DIR}/tests/script_test.py)

file(GLOB DLL_FILES "${Python_LIBRARIES}/*.dll")

foreach(DLL_FILE ${DLL_FILES})
    add_custom_command(TARGET PythonCHelper POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${DLL_FILE}
            ${CMAKE_CURRENT_BINARY_DIR}/tests)
endforeach()
