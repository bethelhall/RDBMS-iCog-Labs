cmake_minimum_required (VERSION 3.8)
project (RDBM_USING_SETTHEORY)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# creates the variable EXEC and sets it to main
set(EXEC main)
# add include directories
include_directories(../include ../src)
# add executable file
add_executable(${EXEC} 
				main.cpp 
				TableClass.cpp 
				TupleClass.cpp 
				AttributeClass.cpp 
				DatabaseClass.cpp
				setOperation.cpp
				queryParser.cpp
				helperFunctions.cpp
				)
set_property(TARGET ${EXEC} PROPERTY POSITION_INDEPENDENT_CODE ON)

add_library(header SHARED 
			TableClass.cpp
			TupleClass.cpp 
			AttributeClass.cpp 
			DatabaseClass.cpp
			setOperation.cpp
			queryParser.cpp 
			helperFunctions.cpp
			main.cpp
			)
set_property(TARGET header PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE ON)

target_link_libraries(${EXEC} header)