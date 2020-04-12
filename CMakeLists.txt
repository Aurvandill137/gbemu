cmake_minimum_required(VERSION 3.13)
project(gb_emu)

set(CMAKE_CXX_STANDARD 14)

add_executable(gb_emu main.cpp cpu.cpp cpu.h mmu.cpp mmu.h opcode_functions.h opcode_functions.cpp cartridge.cpp cartridge.h)
target_link_libraries(gb_emu -lOpenGL32 -lfreeGLUT)