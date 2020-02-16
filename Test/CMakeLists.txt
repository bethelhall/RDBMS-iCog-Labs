cmake_minimum_required (VERSION 3.8)
project (RDBM_USING_SETTHEORY)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)


# add include directories
include_directories(../include ../src)

set(CXXTEST_CURRENT_SOURCE_DIR)
find_package(CxxTest)
if(CXXTEST_FOUND)
    include_directories(/usr/include/)
    enable_testing()

    CXXTEST_ADD_TEST(unittest testTable.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/TestSuite.hpp)
    target_link_libraries(unittest header)

endif()
