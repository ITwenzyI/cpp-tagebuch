cmake_minimum_required(VERSION 3.10)
project(DigitalesTagebuch)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(DigitalesTagebuch main.cpp ${SOURCES})
