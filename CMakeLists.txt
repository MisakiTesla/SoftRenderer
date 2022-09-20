cmake_minimum_required(VERSION 3.22)
project(SoftRenderer)

set(CMAKE_CXX_STANDARD 14)

add_executable(SoftRenderer main.cpp TGAImage.cpp TGAImage.h)
