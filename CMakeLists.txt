cmake_minimum_required(VERSION 3.22)
project(SoftRenderer)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=UTF-16")
#add_executable(SoftRenderer main.cpp TGAImage.cpp TGAImage.h)
add_executable(SoftRenderer WIN32 mainWindow.cpp)

