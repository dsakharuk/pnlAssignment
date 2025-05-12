cmake_minimum_required(VERSION 3.10)

# Project name and version
 project(MyApp VERSION 1.0)
 
# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(myProject pnl.cpp)
