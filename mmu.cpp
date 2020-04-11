//
// Created by Ole H. on 12.05.2019.
//

#include <cstdint>
#include "opcode_functions.h"
#include "cartridge.h"
#include "cpu.h"
#include "mmu.h"

/*
 * Memory Map
 * 0x0000 - 0x3FFF - 16kB - rom bank 1
 * 0x4000 - 0x7FFF - 16kB - switchable rom bank
 * 0x8000 - 0x9FFF -  8kB - video ram
 * 0xA000 - 0xBFFF -  8kB - swithable ram bank
 * 0xC000 - 0xDFFF -  8kB - Internal RAM
 * 0xE000 - 0xFDFF - Internal RAM Mirror
 * 0xFE00 - 0xFE9F - Sprite Atrib memory
 * 0xFEA0 - 0xFEFF - empty but unusable for IO
 * 0xFF00 - 0xFF4B - IO PORTS
 * 0xFF4C - 0xFF7F - empty but unsuable for IO
 * 0xFF80 - 0xFFFE - Internal RAM
 * 0xFFFF          - Interrupt enable regsiter
 */
uint8_t mem[0xFFFF]; //memory

//TODO: add mbc Controller emulation
//TODO: add missing functionaity in write_adress
//TODO: add missing functionality in read_adress
//TODO: add read only and echo areas in memory

void write_address(uint8_t data, uint16_t address){

    mem[address] = data;
    //need to include write protection

}
unsigned char read_address(uint16_t address){

    return mem[address];
}

