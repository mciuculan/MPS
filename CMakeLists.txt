cmake_minimum_required(VERSION 3.10)
project(MpsProject)

set( CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe" )
set( CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe" )

include_directories(main)

add_subdirectory(main)
add_subdirectory(test)
add_subdirectory(lib/googletest)

cmake_minimum_required(VERSION 3.12) # version can be different

project(my_cpp_project) #name of your project

add_subdirectory(lib/googletest) # add googletest subdirectory

include_directories(lib/googletest/include) # this is so we can #include <gtest/gtest.h>

# add_executable(mytests mytests.cpp) # add this executable

# target_link_libraries(mytests PRIVATE gtest) # link google test to this executable