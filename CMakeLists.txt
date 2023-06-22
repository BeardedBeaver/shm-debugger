cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 20)

project(shmd)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

add_subdirectory(shmd-lib)
add_subdirectory(shmd-tests)
add_subdirectory(shmd-dumper)
add_subdirectory(shmd-emulator)
