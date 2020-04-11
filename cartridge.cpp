#include <iostream>
#include "cpu.h"
#include "mmu.h"
#include "opcode_functions.h"
#include "cartridge.h"
using namespace std;

uint8_t cartridge[0x200000];