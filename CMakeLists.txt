cmake_minimum_required(VERSION 3.22)
project(SoftRenderer)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=UTF-16")

# 声明一个变量SDL2_DIR为SDL2安装路径
set(SDL2_DIR SDL2/SDL2-2.24.0/x86_64-w64-mingw32)
# 设置要包含的头文件的路径
include_directories(${SDL2_DIR}/include/SDL2)
# 设置要关联的库的路径
link_directories(${SDL2_DIR}/bin)

#add_executable(SoftRenderer main.cpp TGAImage.cpp TGAImage.h)
#add_executable(SoftRenderer WIN32 mainWindow.cpp)
add_executable(SoftRenderer main.cpp TGAImage.cpp TGAImage.h)

target_link_libraries(SoftRenderer mingw32 SDL2 SDL2main)