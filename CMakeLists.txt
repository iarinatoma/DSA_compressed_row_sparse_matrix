cmake_minimum_required(VERSION 3.30)
project(Matrix)

set(CMAKE_CXX_STANDARD 20)

add_executable(Matrix App.cpp ShortTest.cpp ExtendedTest.cpp Matrix.cpp)
