//
// Created by Ole H. on 12.05.2019.
//

#ifndef UNTITLED1_CPU_H
#define UNTITLED1_CPU_H

void interpret(unsigned short instrcution);
void halt();
void nop();
//LD Functions
void load(uint8_t *a, uint8_t b);
void load_to_mem(uint16_t address, uint8_t data);
void load_from_mem(uint8_t* reg, uint16_t address);
void load_2B(uint8_t *reg1, uint8_t *reg2);
void load_1B(uint8_t *reg);
void load_1B(uint16_t address);

//increment and decrement functions
void increment(uint8_t *var);
void decrement(uint8_t *var);
void increment(uint8_t *var1, uint8_t *var2);
void decrement(uint8_t *var, uint8_t *var2);
void increment(uint16_t address);
void decrement(uint16_t address);

//bit Logic Operations

void rlc(uint8_t *var);
void rlca(); //basicaly rlc on register A with half the cpu cykles

#endif //UNTITLED1_CPU_H
