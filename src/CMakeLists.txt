cmake_minimum_required (VERSION 3.8)
project (RDBM_USING_SETTHEORY)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# creates the variable EXEC and sets it to hello
set(EXEC main)

add_executable(${EXEC} 
				main.cpp 
				TableClass.cpp 
				TupleClass.cpp 
				AttributeClass.cpp 
				DatabaseClass.cpp
				setOperation.cpp
				helperFunctions.cpp
				)