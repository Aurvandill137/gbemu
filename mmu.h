//
// Created by Ole H. on 12.05.2019.
//

#ifndef GBEMU_MMU_H
#define GBEMU_MMU_H

void write_address(uint8_t data, uint16_t address);
unsigned char read_address(uint16_t address);

#endif //GBEMU_MMU_H
