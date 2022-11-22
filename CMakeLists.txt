cmake_minimum_required(VERSION 3.21)
project(MatGraf)

set(CMAKE_CXX_STANDARD 14)

add_executable(MatGraf main.cpp src/Vector.cpp include/Vector.h src/Matrix.cpp include/Matrix.h src/Quaternion.cpp include/Quaternion.h)
