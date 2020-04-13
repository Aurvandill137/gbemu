#include <iostream>
#include "opcode_functions.h"
#include "cartridge.h"
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




//misc
///////////////////////////////////////////////////////////////////
//HALT
void halt(){

    //TODO: implement halt
    pc++;
}
//NOP
void nop(){
    pc++;
    cpu_cycles = 1;
}
//CCF
void ccf(){
    flags = flags^(1 << CARRYFLAG);
    cpu_cycles += 1;
    pc++;
}
//CPL
void cpl(){
    a = ~a;
    cpu_cycles += 1;
    pc++;
}
//DAA
void daa(){

}
//DI
void di(){

}
//EI
void ei(){

}
//SCF
void scf(){

}
//STOP
void stop(){

}


//            LOADs
/////////////////////////////////////////////////////////////////////////////////////////////

//LDr8,r8
void ld(uint8_t *a,uint8_t b){
    *a=b;
    cpu_cycles = 1;
    pc++;
}

//LDr8,d8
void ld(uint8_t *a){
    uint8_t b = read_address(pc+1);
    *a=b;
    cpu_cycles = 2;
    pc+=2;
}

//LDr16,d16
void ld(uint8_t *reg1, uint8_t *reg2){
    *reg1 = read_address(pc+1);
    *reg2 = read_address(pc+2);
    cpu_cycles = 3;
    pc+=3;
}

//LD(HL),r8
void ld(uint16_t address,uint8_t b){
    write_address(b,address);
    cpu_cycles+=2;
    pc++;
}

//LD(HL),d8
void ld(uint16_t address){
    write_address(read_address(pc+1),address);
    cpu_cycles+=3;
    pc+=2;
}
//LDr8,(HL)
void ld(uint8_t *a,uint16_t address){
    *a=read_address(address);
    cpu_cycles+=2;
    pc++;
}

//LD (r16),a
void ld_a(uint16_t adress){
    write_address(a,adress);
    cpu_cycles+=2;
    pc++;
}
//LD (d16),A
void ld_a(){
    uint16_t tmp = (read_address(pc+1)<<8) | read_address(pc+2);
    write_address(a,tmp);
    cpu_cycles+=2;
    pc+=2;
}
//LDH (d16),A
void ldh(){

    uint16_t tmp = (read_address(pc+1)<<8) | read_address(pc+2);
    if(tmp >= 0xFF00 && tmp < 0xFFFF){
        write_address(a,tmp);
    }
    cpu_cycles+=4;
    pc+=2;
}
//LDH (C),A
void ldh(uint8_t c){

    write_address(a,0xFF00+c);
    cpu_cycles+=2;
    pc++;
}
//LD A,(r16)
void ld_to_a(uint16_t path){
    a = read_address(path);
    cpu_cycles+=2;
    pc++;
}
//LD A,(d16)
void ld_to_a(){
    uint16_t tmp = (read_address(pc+1)<<8) | read_address(pc+2);
    a=read_address(tmp);
    cpu_cycles+=4;
    pc+=3;
}
//LDH A,(d16)
void ldh_to_a(){
    uint16_t tmp = (read_address(pc+1)<<8) | read_address(pc+2);
    if(tmp >= 0xFF00 && tmp < 0xFFFF){
        a=read_address(tmp);
    }
    cpu_cycles+=3;
    pc+=2;
}
//LDH A,(C)
void ldh_to_a(uint8_t c){
    
    a=read_address(0xFF00+c);    
    cpu_cycles+=2;
    pc++;
}
//LD (HLI),A
void ldi_a(){
    write_address(a,HL);
    uint16_t tmp = HL + 1;
    h = tmp>>8;
    l = tmp;
    cpu_cycles+=2;
    pc++;
}
//LD (HLD),A
void ldd_a(){
    write_address(a,HL);
    uint16_t tmp = HL - 1;
    h = tmp>>8;
    l = tmp;
    cpu_cycles+=2;
    pc++;
}
//LD A,(HLI)
void ldi_to_a(){
    a = read_address(HL);
    uint16_t tmp = HL;
    tmp++;
    h = tmp>>8;
    l = tmp;
    cpu_cycles+=2;
    pc++;
}
//LD A,(HLD)
void ldd_to_a(){
    a = read_address(HL);
    uint16_t tmp = HL;
    tmp--;
    h = tmp>>8;
    l = tmp;
    cpu_cycles+=2;
    pc++;
}
//LD SP,d16
void ld_sp(){

}
//LD [d16],SP
void ld_sp_to_mem(){
    uint16_t address = read_address(pc+1)<<8 | read_address(pc+2);
    write_address(uint8_t(sp>>8), address);
    write_address(uint8_t(sp),address+1);
    cpu_cycles+=5;
    pc +=3;

}
//LD HL,SP+d8
void ld_hl_sp_d8(){
    int8_t d8 = (int8_t)read_address(pc+1);
    uint16_t tmp = sp+d8;
    h = tmp>>8;
    l=tmp;
    clear_flag(ZEROFLAG);
    clear_flag(SUBTRACTFLAG);
    if((int32_t(d8) + uint32_t(pc)) > 0xFFFF){
        set_flag(CARRYFLAG);
    } else {
        clear_flag(CARRYFLAG);
    }
    if(((pc & 0x0FFF) + (int16_t) d8) > 0x0FFF){
        set_flag(CARRYFLAG);
    } else {
        clear_flag(CARRYFLAG);
    }

    cpu_cycles+=3;
    pc+=2;
}
//LD SP,HL
void ld_sp_hl(){
    sp = HL;
    cpu_cycles +=2;
    pc++;
}


//                  INCREMENT/DECREMENT
//////////////////////////////////////////////////////////////////////

void increment(uint8_t *var){
    //Reset subtract flag
    flags &= ~(1<<SUBTRACTFLAG);
    //check if the halfcarryflag needs to be set
    if((*var&0x0F) != 0){
        set_flag(HALFCARRYFLAG);
    }else {
        clear_flag(HALFCARRYFLAG);
    }
    if(*var == 0xFF){
        *var=0;
        //set Zeroflag
        set_flag(ZEROFLAG);
    }else {
        clear_flag(ZEROFLAG);
        *var += 1;
    }
    cpu_cycles = 2;
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
    cpu_cycles = 2;
    pc++;
}
void increment(uint16_t *sp){
    if(*sp == 0xFFFF){
        *sp=0;
    }else {
        *sp++;
    }
    cpu_cycles = 2;
    pc++;
}

void increment(uint16_t address){
    uint8_t x = read_address(address);
    increment(&x);
    write_address(x,address);
    cpu_cycles+=4; //add 4 cycles to get 12 cycles
}

void decrement(uint8_t *var){
    //Reset subtract flag
    clear_flag(SUBTRACTFLAG);
    //check if the halfcarryflag needs to be set
    if((*var&0x0F) == 0){
        set_flag(HALFCARRYFLAG);
    }else {
        clear_flag(HALFCARRYFLAG);
    }
    if(*var == 0){
        *var=0xFF;
    }else {
        *var-=1;
    }
    if(*var == 0){
        set_flag(ZEROFLAG);
    } else {
        clear_flag(ZEROFLAG);
    }
    cpu_cycles = 2;
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
    cpu_cycles = 2;
    pc++;
}
void decrement(uint16_t *sp){
    if(*sp == 0xFFFF){
        *sp=0;
    }else {
        *sp++;
    }
    cpu_cycles = 2;
    pc++;
}

void decrement(uint16_t address){
    uint8_t x = read_address(address);
    decrement(&x);
    write_address(x,address);
    cpu_cycles+=1; //add 1 cycles to get 3 cycles
}


//              BIT Ops
/////////////////////////////////////////////////////////////////////

void swap(uint8_t *var){
    uint8_t tmp = *var;
    *var = (*var>>4) | (tmp<<4);
    cpu_cycles+=8;
    clear_flag(CARRYFLAG);
    clear_flag(SUBTRACTFLAG);
    clear_flag(HALFCARRYFLAG);
    if(*var == 0){
        set_flag(ZEROFLAG);
    }else {
        clear_flag(ZEROFLAG);
    }
    pc++;
}
void swap(uint16_t address){
    uint8_t x = read_address(address);
    uint8_t tmp = x;
    x = (x>>4) | (tmp<<4);
    write_address(x,address);
    cpu_cycles+=3;
    clear_flag(CARRYFLAG);
    clear_flag(SUBTRACTFLAG);
    clear_flag(HALFCARRYFLAG);
    if(x == 0){
        set_flag(ZEROFLAG);
    }else {
        clear_flag(ZEROFLAG);
    }
    pc++;
}
void res(uint8_t bit, uint8_t *reg){
    *reg &= ~(1<<bit);
    cpu_cycles+=2;
    pc++;
}
void res(uint8_t bit, uint16_t address){
    uint8_t x = read_address(address);
    res(bit, &x);
    write_address(x,address);
    cpu_cycles+=2;
}
void set(uint8_t bit, uint8_t *reg){
    *reg |= (1<<bit);
    cpu_cycles+=2;
    pc++;
}
void set(uint8_t bit, uint16_t address){
    uint8_t x = read_address(address);
    set(bit, &x);
    write_address(x,address);
    cpu_cycles+=2;
}
void bit(uint8_t bittest, uint8_t *var){
    cpu_cycles+=2;
    pc+=2;
    clear_flag(SUBTRACTFLAG);
    set_flag(HALFCARRYFLAG);
    if ((*var&(1<<bittest))==0){
        set_flag(ZEROFLAG);
    } else{
        clear_flag(ZEROFLAG);
    }
}
void bit(uint8_t bittest, uint16_t address){
    cpu_cycles+=1;
    uint8_t x = read_address(address);
    bit(bittest,&x);
}


//              Bit Shifting
/////////////////////////////////////////////////////////////////


void rlc(uint8_t *var){
    uint8_t tmp = *var;
    *var = (*var<<1) | (tmp & 0b10000000)>>7;
    pc++;
    cpu_cycles = 2;
    //reset all flags
    flags = 0;
    //set carry flag or unset it
    if((*var & 1) != 0){
        set_flag(CARRYFLAG);
    } else {
        clear_flag(CARRYFLAG);
    }
    if(*var != 0){
        clear_flag(ZEROFLAG);
    } else {
        set_flag(ZEROFLAG);
    }
    clear_flag(HALFCARRYFLAG);
    clear_flag(SUBTRACTFLAG);
    pc++;
}
void rlc(uint16_t address){
    uint8_t x = read_address(address);
    rlc(&x);
    write_address(x,address);
    cpu_cycles+=2;
}
void rlca(){
    uint8_t tmp = a;
    a = (a<<1) | (tmp & 0b10000000)>>7;
    pc++;
    cpu_cycles = 1;
    //reset all flags
    flags = 0;
    //set carry flag or unset it
    if((a & 1) != 0){
        set_flag(CARRYFLAG);
    } else {
       clear_flag(CARRYFLAG);
    }
    clear_flag(ZEROFLAG);
    clear_flag(HALFCARRYFLAG);
    clear_flag(SUBTRACTFLAG);
    pc++;
}
//                      helpers
////////////////////////////////////////////////////////////////////////////////////////
void set_flag(uint8_t flag){
    flags |= (1<<flag);
}
void clear_flag(uint8_t flag){
     flags &= ~(1<<flag);
}

//ALU
////////////////////////////////////////////////////////////////////////////////////////

//ADC A,r8
void alu_adc(uint8_t r8){
    uint16_t n = a+r8;
    if(flags&(1<<CARRYFLAG)){
        n++;
    }
    if(a == 0){
        set_flag(ZEROFLAG);
    } else{
        clear_flag(ZEROFLAG);
    }
    clear_flag(SUBTRACTFLAG);
    if(((a&0x0F)+(r8&0x0F))&0x10 == 0x10){
        set_flag(HALFCARRYFLAG);
    } else {
        clear_flag(HALFCARRYFLAG);
    }
    if((uint16_t)n > 0xFF){
        set_flag(HALFCARRYFLAG);
    } else {
        clear_flag(HALFCARRYFLAG);
    }
    a = n&&0xFF;
    cpu_cycles++;
    pc++;
}
//ADC A,[HL]
void alu_adc(uint16_t address){
    uint8_t r8 = read_address(address);
    uint16_t n = a+r8;
    n=a+r8;
    if(flags&(1<<CARRYFLAG)){
        n++;
    }
    if(a == 0){
        set_flag(ZEROFLAG);
    } else{
        clear_flag(ZEROFLAG);
    }
    clear_flag(SUBTRACTFLAG);
    if(((a&0x0F)+(r8&0x0F))&0x10 == 0x10){
        set_flag(HALFCARRYFLAG);
    } else {
        clear_flag(HALFCARRYFLAG);
    }
    if((uint16_t)n > 0xFF){
        set_flag(HALFCARRYFLAG);
    } else {
        clear_flag(HALFCARRYFLAG);
    }
    a = n&&0xFF;
    cpu_cycles+=2;
    pc++;
}
//ADC A,n8
void alu_adc(){
    uint8_t r8 = read_address(pc+1);
    uint16_t n = a+r8;
    n=a+r8;
    if(flags&(1<<CARRYFLAG)){
        n++;
    }
    if(a == 0){
        set_flag(ZEROFLAG);
    } else{
        clear_flag(ZEROFLAG);
    }
    clear_flag(SUBTRACTFLAG);
    if(((a&0x0F)+(r8&0x0F))&0x10 == 0x10){
        set_flag(HALFCARRYFLAG);
    } else {
        clear_flag(HALFCARRYFLAG);
    }
    if((uint16_t)n > 0xFF){
        set_flag(HALFCARRYFLAG);
    } else {
        clear_flag(HALFCARRYFLAG);
    }
    a = n&&0xFF;
    cpu_cycles+=2;
    pc+=2;
}
//ADD A,r8
void alu_add(uint8_t r8){
    uint16_t n = a+r8;
    if(a == 0){
        set_flag(ZEROFLAG);
    } else{
        clear_flag(ZEROFLAG);
    }
    clear_flag(SUBTRACTFLAG);
    if(((a&0x0F)+(r8&0x0F))&0x10 == 0x10){
        set_flag(HALFCARRYFLAG);
    } else {
        clear_flag(HALFCARRYFLAG);
    }
    if((uint16_t)n > 0xFF){
        set_flag(HALFCARRYFLAG);
    } else {
        clear_flag(HALFCARRYFLAG);
    }
    a = n&&0xFF;
    cpu_cycles++;
    pc++;

}
//ADD A,[HL]
void alu_add(uint16_t address){
    uint8_t r8 = read_address(address);
    uint16_t n = a+r8;
    n=a+r8;
    if(a == 0){
        set_flag(ZEROFLAG);
    } else{
        clear_flag(ZEROFLAG);
    }
    clear_flag(SUBTRACTFLAG);
    if(((a&0x0F)+(r8&0x0F))&0x10 == 0x10){
        set_flag(HALFCARRYFLAG);
    } else {
        clear_flag(HALFCARRYFLAG);
    }
    if((uint16_t)n > 0xFF){
        set_flag(HALFCARRYFLAG);
    } else {
        clear_flag(HALFCARRYFLAG);
    }
    a = n&&0xFF;
    cpu_cycles+=2;
    pc++;
}
//ADD A,n8
void alu_add(){
    uint8_t r8 = read_address(pc+1);
    uint16_t n = a+r8;
    n=a+r8;
    if(a == 0){
        set_flag(ZEROFLAG);
    } else{
        clear_flag(ZEROFLAG);
    }
    clear_flag(SUBTRACTFLAG);
    if(((a&0x0F)+(r8&0x0F))&0x10 == 0x10){
        set_flag(HALFCARRYFLAG);
    } else {
        clear_flag(HALFCARRYFLAG);
    }
    if((uint16_t)n > 0xFF){
        set_flag(HALFCARRYFLAG);
    } else {
        clear_flag(HALFCARRYFLAG);
    }
    a = n&&0xFF;
    cpu_cycles+=2;
    pc+=2;
}
//ADD HL,r16
void alu_add_HL(uint16_t r16){

}
//AND A,r8
void alu_and(uint8_t r8){
    a = a&r8;
    if(a == 0){
        set_flag(ZEROFLAG);
    } else {
        clear_flag(ZEROFLAG);
    }
    clear_flag(SUBTRACTFLAG);
    set_flag(HALFCARRYFLAG);
    clear_flag(CARRYFLAG);
    cpu_cycles+=1;
    pc++;
}
//AND A,[HL]
void alu_and(uint16_t address){
    uint8_t r8 = read_address(address);
    a = a&r8;
    if(a == 0){
        set_flag(ZEROFLAG);
    } else {
        clear_flag(ZEROFLAG);
    }
    clear_flag(SUBTRACTFLAG);
    set_flag(HALFCARRYFLAG);
    clear_flag(CARRYFLAG);
    cpu_cycles+=2;
    pc++;
}
//AND A,n8
void alu_and(){
    uint8_t r8 = read_address(pc+1);
    a = a&r8;
    if(a == 0){
        set_flag(ZEROFLAG);
    } else {
        clear_flag(ZEROFLAG);
    }
    clear_flag(SUBTRACTFLAG);
    set_flag(HALFCARRYFLAG);
    clear_flag(CARRYFLAG);
    cpu_cycles+=2;
    pc+=2;
}
//CP A,r8
void alu_cp(uint8_t r8){
    uint16_t tmp = (uint16_t) a - r8;
    if(tmp == 0){
        set_flag(ZEROFLAG);
    } else {
        clear_flag(ZEROFLAG);
    }
    set_flag(SUBTRACTFLAG);
    if(((a&0x0F)+(r8&0x0F))&0x10 == 0x10){
        set_flag(HALFCARRYFLAG);
    } else {
        clear_flag(HALFCARRYFLAG);
    }
    if(tmp > 0xFF){
        set_flag(HALFCARRYFLAG);
    } else {
        clear_flag(HALFCARRYFLAG);
    }
    cpu_cycles+=1;
    pc++;

}
//CP A,[HL]
void alu_cp(uint16_t address){
    uint8_t r8 = read_address(address);
    uint16_t tmp = (uint16_t) a - r8;
    if(tmp == 0){
        set_flag(ZEROFLAG);
    } else {
        clear_flag(ZEROFLAG);
    }
    set_flag(SUBTRACTFLAG);
    if(((a&0x0F)+(r8&0x0F))&0x10 == 0x10){
        set_flag(HALFCARRYFLAG);
    } else {
        clear_flag(HALFCARRYFLAG);
    }
    if(tmp > 0xFF){
        set_flag(HALFCARRYFLAG);
    } else {
        clear_flag(HALFCARRYFLAG);
    }
    cpu_cycles+=2;
    pc++;

}
//CP A,n8
void alu_cp(){
    uint8_t r8 = read_address(pc+1);
    uint16_t tmp = (uint16_t) a - r8;
    if(tmp == 0){
        set_flag(ZEROFLAG);
    } else {
        clear_flag(ZEROFLAG);
    }
    set_flag(SUBTRACTFLAG);
    if(((a&0x0F)+(r8&0x0F))&0x10 == 0x10){
        set_flag(HALFCARRYFLAG);
    } else {
        clear_flag(HALFCARRYFLAG);
    }
    if(tmp > 0xFF){
        set_flag(HALFCARRYFLAG);
    } else {
        clear_flag(HALFCARRYFLAG);
    }
    cpu_cycles+=2;
    pc+=2;
}
//OR A,r8
void alu_or(uint8_t r8){

    a = a|r8;
    if(a == 0){
        set_flag(ZEROFLAG);
    } else {
        clear_flag(ZEROFLAG);
    }
    clear_flag(SUBTRACTFLAG);
    clear_flag(HALFCARRYFLAG);
    clear_flag(CARRYFLAG);
    pc++;
    cpu_cycles+=1;
}
//OR A,[HL]
void alu_or(uint16_t address){
    uint8_t r8 = read_address(address);
    a = a|r8;
    if(a == 0){
        set_flag(ZEROFLAG);
    } else {
        clear_flag(ZEROFLAG);
    }
    clear_flag(SUBTRACTFLAG);
    clear_flag(HALFCARRYFLAG);
    clear_flag(CARRYFLAG);
    pc++;
    cpu_cycles+=2;

}
//OR A,n8
void alu_or(){
    uint8_t r8 = read_address(pc+1);
    a = a|r8;
    if(a == 0){
        set_flag(ZEROFLAG);
    } else {
        clear_flag(ZEROFLAG);
    }
    clear_flag(SUBTRACTFLAG);
    clear_flag(HALFCARRYFLAG);
    clear_flag(CARRYFLAG);
    pc+=2;
    cpu_cycles+=2;
}
//SBC A,r8
void alu_sbc(uint8_t r8){
    
}
//SBC A,[HL]
void alu_sbc(uint16_t address){
    
}
//SBC A,n8
void alu_sbc(){
    
}
//SUB A,r8
void alu_sub(uint8_t r8){

}
//SUB A,[HL]
void alu_sub(uint16_t address){
    
}
//SUB A,n8
void alu_sub(){
    
}
//XOR A,r8
void alu_xor(uint8_t r8){
    a = a^r8;
    if(a == 0){
        set_flag(ZEROFLAG);
    } else {
        clear_flag(ZEROFLAG);
    }
    clear_flag(SUBTRACTFLAG);
    clear_flag(HALFCARRYFLAG);
    clear_flag(CARRYFLAG);
    pc++;
    cpu_cycles+=1;
}
//XOR A,[HL]
void alu_xor(uint16_t address){
    uint8_t r8 = read_address(address);
    a = a^r8;
    if(a == 0){
        set_flag(ZEROFLAG);
    } else {
        clear_flag(ZEROFLAG);
    }
    clear_flag(SUBTRACTFLAG);
    clear_flag(HALFCARRYFLAG);
    clear_flag(CARRYFLAG);
    pc++;
    cpu_cycles+=2;
}
//XOR A,n8
void alu_xor(){
    uint8_t r8 = read_address(pc+1);
    a = a^r8;
    if(a == 0){
        set_flag(ZEROFLAG);
    } else {
        clear_flag(ZEROFLAG);
    }
    clear_flag(SUBTRACTFLAG);
    clear_flag(HALFCARRYFLAG);
    clear_flag(CARRYFLAG);
    pc+=2;
    cpu_cycles+=2;
}