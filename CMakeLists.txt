cmake_minimum_required(VERSION 3.20)
project(DigitalesTagebuch)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(DigitalesTagebuch ${SOURCES})
target_include_directories(DigitalesTagebuch PRIVATE src)

if (MSVC)
    target_compile_options(DigitalesTagebuch PRIVATE /utf-8)
else()
    target_compile_options(DigitalesTagebuch PRIVATE -finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()
