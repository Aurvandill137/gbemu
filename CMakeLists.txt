cmake_minimum_required(VERSION 3.14)
project(gb_emu)

set(CMAKE_CXX_STANDARD 14)

add_executable(gb_emu main.cpp cpu.cpp cpu.h mmu.cpp mmu.h opcode_functions.h opcode_functions.cpp)