cmake_minimum_required(VERSION 3.22)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")

project(SoftRenderer)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=UTF-16")

#add_executable(SoftRenderer main.cpp TGAImage.cpp TGAImage.h)
#add_executable(SoftRenderer WIN32 mainWindow.cpp)
add_executable(SoftRenderer main.cpp TGAImage.cpp TGAImage.h Game.cpp Game.h Timer.cpp Timer.h)

find_package(sdl2 CONFIG REQUIRED)

#target_link_libraries(SoftRenderer mingw32 SDL2 SDL2main)
target_link_libraries(SoftRenderer PRIVATE SDL2::SDL2 SDL2::SDL2main)
