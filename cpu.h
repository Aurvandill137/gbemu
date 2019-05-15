//
// Created by Ole H. on 12.05.2019.
//

#ifndef UNTITLED1_CPU_H
#define UNTITLED1_CPU_H

void interpret(unsigned short instrcution);
void load(uint8_t *a, uint8_t b);
void load_to_mem(uint16_t address, uint8_t data);
void load_from_mem(uint8_t* reg, uint16_t address);
void halt();
void nop();
void load_2B(uint8_t *reg1, uint8_t *reg2);
void load_1B(uint8_t *reg);

#endif //UNTITLED1_CPU_H
