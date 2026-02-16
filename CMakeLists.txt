cmake_minimum_required(VERSION 3.20)
project(DigitalesTagebuch)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(DigitalesTagebuch src/main.cpp ${SOURCES})
