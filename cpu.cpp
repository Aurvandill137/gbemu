//
// Created by Ole H. on 12.05.2019.
//

#include <iostream>
#include "cpu.h"
#include "mmu.h"

#define HL (h << 8 | l)
#define BC (b << 8 | c)

using namespace std;

uint8_t a;
uint8_t b;
uint8_t c;
uint8_t d;
uint8_t e;
uint8_t h;
uint8_t l;
/*
 * z = zero flag
 * s = subtract flag
 * h = half carry flag
 * c = carry flag
 */
uint8_t flags; //z s h c 0 0 0 0
uint16_t sp;
uint16_t pc;

uint8_t extended_opcode = 0;
uint8_t cpu_cycles = 0;

//Instruction can be 2 bytes so we use an usinged short
void interpret(uint8_t dissassembly){

    //TODO : add missing opcodes

    if( dissassembly == 0xCB){
        extended_opcode = 1;
        pc++;

    }else {

        if (extended_opcode == 0) {

            switch (dissassembly) {
                case (0x00): // NOP
                    nop();
                    break;
                case (0x01): // LD BC,d16
                    b = read_address(pc+1);
                    c = read_address(pc+2);
                    cpu_cycles = 12;
                    pc+=3;
                    break;
                case (0x02): // LD (BC),A
                    load_to_mem(BC,a);
                    break;
                case (0x03): // INC BC
                    if(c == 255){
                        c = 0;
                        if(b == 255){
                            b = 0;
                        } else {
                           c++;
                        }
                    }else {
                        c++;
                    }
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x04): //

                    break;
                case (0x05): //

                    break;
                case (0x06): //

                    break;
                case (0x07): //

                    break;
                case (0x08): //

                    break;
                case (0x09): //

                    break;
                case (0x0A): //

                    break;
                case (0x0B): //

                    break;
                case (0x0C): //

                    break;
                case (0x0D): //

                    break;
                case (0x0E): //

                    break;
                case (0x0F): //

                    break;
                case (0x40): //LD B,B
                    //not necessary to implement
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x41): //LD B,C
                    load(&b,c);
                    break;
                case (0x42): //LD B,D
                    load(&b,d);
                    break;
                case (0x43): //LD B,E
                    load(&b,e);
                    break;
                case (0x44): //LD B,H
                    load(&b,h);
                    break;
                case (0x45): //LD B,L
                    load(&b,l);
                    break;
                case (0x46): //LD B,((HL)
                    load_from_mem(&b,HL);
                    break;
                case (0x47): //LD B,A
                    load(&b,a);
                    break;
                case (0x48): //LD C,B
                    load(&c,b);
                    break;
                case (0x49): //LD C,C
                    // unnecesary to implement
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x4A): //LD C,D
                    load(&c,d);
                    break;
                case (0x4B): //LD C,E
                    load(&c,e);
                    break;
                case (0x4C): //LD C,H
                    load(&c,h);
                    break;
                case (0x4D): //LD C,L
                    load(&c,l);
                    break;
                case (0x4E): //LD C,(HL)
                    load_from_mem(&c,HL);
                    break;
                case (0x4F): //LD C,A
                    load(&c,a);
                    break;
                case (0x50): //LD D,B
                    load(&d,b);
                    break;
                case (0x51): //LD D,B
                    load(&d,c);
                    break;
                case (0x52): //LD D,D
                    //no need to implement
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x53): //LD D,E
                    load(&d,e);
                    break;
                case (0x54): //LD D,H
                    load(&d,h);
                    break;
                case (0x55): //LD D,L
                    load(&d,l);
                    break;
                case (0x56): //LD D,(HL)
                    load_from_mem(&d,HL);
                    break;
                case (0x57): //LD D,A
                    load(&d,a);
                    break;
                case (0x58): //LD E,B
                    load(&e,b);
                    break;
                case (0x59): //LD E,C
                    load(&e,c);
                    break;
                case (0x5A): //LD E,D
                    load(&e,d);
                    break;
                case (0x5B): //LD E,E
                    //no need to implement lel
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x5C): //LD E,H
                    load(&e,h);
                    break;
                case (0x5D): //LD E,L
                    load(&e,l);
                    break;
                case (0x5E): //LD E,(HL)
                    load_from_mem(&e,HL);
                    break;
                case (0x5F): //LD E,A
                    load(&e,a);
                    break;
                case (0x60): //ld H,L
                    load(&h,b);
                    break;
                case (0x61): //ld H,C
                    load(&h,c);
                    break;
                case (0x62): //ld H,D
                    load(&h,d);
                    break;
                case (0x63): //ld H,E
                    load(&h,e);
                    break;
                case (0x64): //ld H,H
                    //no need to implement
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x65): //ld H,L
                    load(&h,l);
                    break;
                case (0x66): // ld H,(HL)
                    load_from_mem(&h,HL);
                    break;
                case (0x67): //ld H,A
                    load(&h,a);
                    break;
                case (0x68): //ld L,B
                    load(&l,b);
                    break;
                case (0x69): //ld L,C
                    load(&l,c);
                    break;
                case (0x6A): //ld L,D
                    load(&l,d);
                    break;
                case (0x6B): //ld L,E
                    load(&l,e);
                    break;
                case (0x6C): //ld l,H
                    load(&l,h);
                    break;
                case (0x6D): //ld L,L
                    //unnecesary to implement
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x6E): //ld L,(HL)
                    load_from_mem(&l,HL);
                    break;
                case (0x6F): //ld L,A
                    load(&l,a);
                    break;
                case (0x70): //1d(HL),B
                    load_to_mem(HL,b);
                    break;
                case (0x71): //1d(HL),C
                    load_to_mem(HL,c);
                    break;
                case (0x72): //1d(HL),D
                    load_to_mem(HL,d);
                    break;
                case (0x73): //1d(HL),E
                    load_to_mem(HL,e);
                    break;
                case (0x74): //1d(HL),H
                    load_to_mem(HL,h);
                    break;
                case (0x75): //1d(HL),L
                    load_to_mem(HL,l);
                    break;
                case (0x76): //HALT
                    halt();
                    break;
                case (0x77): //1d(HL),A
                    load_to_mem(HL,a);
                    break;
                case (0x78): //ld A,B
                    load(&a,b);
                    break;
                case (0x79): //ld A,C
                    load(&a,c);
                    break;
                case (0x7A): //ld A,D
                    load(&a,d);
                    break;
                case (0x7B): //ld A,E
                    load(&a,e);
                    break;
                case (0x7C): //ld A,H
                    load(&a,h);
                    break;
                case (0x7D): //ld A,L
                    load(&a,l);
                    break;
                case (0x7E): //ld A,(HL)
                    load_from_mem(&a,HL);
                    break;
                case (0x7F): //ld A,A
                    //unnecesary to execute
                    cpu_cycles = 4;
                    pc++;
                    break;

                default:
                    cout << "unimplemented opcode" << endl;
            }
        } else {
            extended_opcode = 0;

            switch(dissassembly){


                default:
                    cout << "unimplemented opcode" << endl;
                    break;
            }

        }
    }
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
void halt(){

    //TODO: implement halt
    pc++;
}
void nop(){
    pc++;
    cpu_cycles = 4;
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