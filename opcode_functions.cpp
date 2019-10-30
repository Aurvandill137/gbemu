#include <iostream>
#include "opcode_functions.h"
#include "cpu.h"
#include "mmu.h"

extern uint8_t a;
extern uint8_t b;
extern uint8_t c;
extern uint8_t d;
extern uint8_t e;
extern uint8_t h;
extern uint8_t l;

extern uint8_t flags; //z s h c 0 0 0 0
extern uint16_t sp;
extern uint16_t pc;

extern uint8_t extended_opcode;
extern uint8_t cpu_cycles;


void halt(){

    //TODO: implement halt
    pc++;
}
void nop(){
    pc++;
    cpu_cycles = 4;
}

void load(uint8_t *a, uint8_t b){
    *a = b;
    cpu_cycles = 4;
    pc++;
}
void load_to_mem(uint16_t address, uint8_t data){
    write_address(data, address);
    cpu_cycles = 8;
    pc++;
}
void load_from_mem(uint8_t *reg, uint16_t address){
    *reg = read_address(address);
    cpu_cycles = 8;
    pc++;
}
void load_2B(uint8_t *reg1, uint8_t *reg2){
    *reg1 = read_address(pc+1);
    *reg2 = read_address(pc+2);
    cpu_cycles = 12;
    pc+=3;
}
void load_1B(uint8_t *reg){
    *reg = read_address(pc+1);
    pc+=2;
    cpu_cycles+=2;
}
void load_1B(uint16_t address){
    write_address(read_address(pc+1), address);
    pc+=2;
    cpu_cycles+=2;
}

void increment(uint8_t *var){
    //Reset subtract flag
    flags &= ~(1<<SUBTRACTFLAG);
    //check if the halfcarryflag needs to be set
    if((*var&0x0F) != 0){
        flags |= (1<<HALFCARRYFLAG);
    }else {
        flags &= ~(1<<HALFCARRYFLAG);
    }
    if(*var == 0xFF){
        *var=0;
        //set Zeroflag
        flags |= (1<<ZEROFLAG);
    }else {
        flags &= ~(1<<ZEROFLAG);
        *var += 1;
    }
    cpu_cycles = 8;
    pc++;

}
void decrement(uint8_t *var){
    //Reset subtract flag
    flags &= ~(1<<SUBTRACTFLAG);
    //check if the halfcarryflag needs to be set
    if((*var&0x0F) == 0){
        flags |= (1<<HALFCARRYFLAG);
    }else {
        flags &= ~(1<<HALFCARRYFLAG);
    }
    if(*var == 0){
        *var=0xFF;
    }else {
        *var-=1;
    }
    if(*var == 0){
        flags |= (1<<ZEROFLAG);
    } else {
        flags &= ~(1<<ZEROFLAG);
    }
    cpu_cycles = 8;
    pc++;
}
void increment(uint8_t *var1, uint8_t *var2){

    uint16_t x = *var1<<8 | *var2;
    if(x == 0xFFFF){
        x=0;
    }else {
        x++;
    }
    *var1 = x>>8;
    *var2 = x&0x00FF;
    cpu_cycles = 8;
    pc++;
}
void decrement(uint8_t *var1, uint8_t *var2){
    uint16_t x = *var1<<8 | *var2;
    if(x == 0){
        x=0xFFFF;
    } else {
        x--;
    }
    *var1 = x>>8;
    *var2 = x&0x00FF;
    cpu_cycles = 8;
    pc++;
}
void decrement(uint16_t address){
    uint8_t x = read_address(address);
    decrement(&x);
    write_address(x,address);
    cpu_cycles+=4; //add 4 cycles to get 12 cycles
}
void increment(uint16_t address){
    uint8_t x = read_address(address);
    increment(&x);
    write_address(x,address);
    cpu_cycles+=4; //add 4 cycles to get 12 cycles
}

void rlc(uint8_t *var){
    uint8_t tmp = *var;
    *var = (*var<<1) | (tmp & 0b10000000)>>7;
    pc++;
    cpu_cycles = 8;
    //reset all flags
    flags = 0;
    //set carry flag or unset it
    if((*var & 1) != 0){
        flags |= (1<<CARRYFLAG);
    } else {
        flags &= ~(1<<CARRYFLAG);
    }
    if(*var != 0){
        flags |= (1<<ZEROFLAG);
    }
}
void rlca(){
    uint8_t tmp = a;
    a = (a<<1) | (tmp & 0b10000000)>>7;
    pc++;
    cpu_cycles = 4;
    //reset all flags
    flags = 0;
    //set carry flag or unset it
    if((a & 1) != 0){
        flags |= (1<<CARRYFLAG);
    } else {
        flags &= ~(1<<CARRYFLAG);
    }
}