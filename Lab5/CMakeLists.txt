cmake_minimum_required(VERSION 3.22)
project(Lab5 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

find_package(OpenCV REQUIRED)
add_executable(Lab5 Main.cpp)
target_link_libraries(Lab5 ${OpenCV_LIBS})