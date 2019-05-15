//
// Created by Ole H. on 12.05.2019.
//

#include <iostream>
#include "cpu.h"
#include "mmu.h"

#define HL (h << 8 | l)
#define BC (b << 8 | c)
#define ZEROFLAG 7
#define SUBTRACTFLAG 6
#define HALFCARRYFLAG 5
#define CARRYFLAG 4

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
                    load_2B(&b,&c);
                    break;
                case (0x02): // LD (BC),A
                    load_to_mem(BC,a);
                    break;
                case (0x03): // INC BC
                    increment(&b,&c);
                    break;
                case (0x04): // INC B
                    increment(&b);
                    break;
                case (0x05): // DEC B
                    decrement(&b);
                    break;
                case (0x06): // LD B,d8
                    load_1B(&b);
                    break;
                case (0x07): // RLCA
                    rlca();
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
                case (0x10): //

                    break;
                case (0x11): //

                    break;
                case (0x12): //

                    break;
                case (0x13): //

                    break;
                case (0x14): //

                    break;
                case (0x15): //

                    break;
                case (0x16): //

                    break;
                case (0x17): //

                    break;
                case (0x18): //

                    break;
                case (0x19): //

                    break;
                case (0x1A): //

                    break;
                case (0x1B): //

                    break;
                case (0x1C): //

                    break;
                case (0x1D): //

                    break;
                case (0x1E): //

                    break;
                case (0x1F): //

                    break;
                case (0x20): //

                    break;
                case (0x21): //

                    break;
                case (0x22): //

                    break;
                case (0x23): //

                    break;
                case (0x24): //

                    break;
                case (0x25): //

                    break;
                case (0x26): //

                    break;
                case (0x27): //

                    break;
                case (0x28): //

                    break;
                case (0x29): //

                    break;
                case (0x2A): //

                    break;
                case (0x2B): //

                    break;
                case (0x2C): //

                    break;
                case (0x2D): //

                    break;
                case (0x2E): //

                    break;
                case (0x2F): //

                    break;
                case (0x30): //

                    break;
                case (0x31): //

                    break;
                case (0x32): //

                    break;
                case (0x33): //

                    break;
                case (0x34): //

                    break;
                case (0x35): //

                    break;
                case (0x36): //

                    break;
                case (0x37): //

                    break;
                case (0x38): //

                    break;
                case (0x39): //

                    break;
                case (0x3A): //

                    break;
                case (0x3B): //

                    break;
                case (0x3C): //

                    break;
                case (0x3D): //

                    break;
                case (0x3E): //

                    break;
                case (0x3F): //

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
                case (0x80): //

                    break;
                case (0x81): //

                    break;
                case (0x82): //

                    break;
                case (0x83): //

                    break;
                case (0x84): //

                    break;
                case (0x85): //

                    break;
                case (0x86): //

                    break;
                case (0x87): //

                    break;
                case (0x88): //

                    break;
                case (0x89): //

                    break;
                case (0x8A): //

                    break;
                case (0x8B): //

                    break;
                case (0x8C): //

                    break;
                case (0x8D): //

                    break;
                case (0x8E): //

                    break;
                case (0x8F): //

                    break;
                case (0x90): //

                    break;
                case (0x91): //

                    break;
                case (0x92): //

                    break;
                case (0x93): //

                    break;
                case (0x94): //

                    break;
                case (0x95): //

                    break;
                case (0x96): //

                    break;
                case (0x97): //

                    break;
                case (0x98): //

                    break;
                case (0x99): //

                    break;
                case (0x9A): //

                    break;
                case (0x9B): //

                    break;
                case (0x9C): //

                    break;
                case (0x9D): //

                    break;
                case (0x9E): //

                    break;
                case (0x9F): //

                    break;
                case (0xA0): //

                    break;
                case (0xA1): //

                    break;
                case (0xA2): //

                    break;
                case (0xA3): //

                    break;
                case (0xA4): //

                    break;
                case (0xA5): //

                    break;
                case (0xA6): //

                    break;
                case (0xA7): //

                    break;
                case (0xA8): //

                    break;
                case (0xA9): //

                    break;
                case (0xAA): //

                    break;
                case (0xAB): //

                    break;
                case (0xAC): //

                    break;
                case (0xAD): //

                    break;
                case (0xAE): //

                    break;
                case (0xAF): //

                    break;
                case (0xB0): //

                    break;
                case (0xB1): //

                    break;
                case (0xB2): //

                    break;
                case (0xB3): //

                    break;
                case (0xB4): //

                    break;
                case (0xB5): //

                    break;
                case (0xB6): //

                    break;
                case (0xB7): //

                    break;
                case (0xB8): //

                    break;
                case (0xB9): //

                    break;
                case (0xBA): //

                    break;
                case (0xBB): //

                    break;
                case (0xBC): //

                    break;
                case (0xBD): //

                    break;
                case (0xBE): //

                    break;
                case (0xBF): //

                    break;
                case (0xC0): //

                    break;
                case (0xC1): //

                    break;
                case (0xC2): //

                    break;
                case (0xC3): //

                    break;
                case (0xC4): //

                    break;
                case (0xC5): //

                    break;
                case (0xC6): //

                    break;
                case (0xC7): //

                    break;
                case (0xC8): //

                    break;
                case (0xC9): //

                    break;
                case (0xCA): //

                    break;
                case (0xCB): //

                    break;
                case (0xCC): //

                    break;
                case (0xCD): //

                    break;
                case (0xCE): //

                    break;
                case (0xCF): //

                    break;
                case (0xD0): //

                    break;
                case (0xD1): //

                    break;
                case (0xD2): //

                    break;
                case (0xD3): //

                    break;
                case (0xD4): //

                    break;
                case (0xD5): //

                    break;
                case (0xD6): //

                    break;
                case (0xD7): //

                    break;
                case (0xD8): //

                    break;
                case (0xD9): //

                    break;
                case (0xDA): //

                    break;
                case (0xDB): //

                    break;
                case (0xDC): //

                    break;
                case (0xDD): //

                    break;
                case (0xDE): //

                    break;
                case (0xDF): //

                    break;
                case (0xE0): //

                    break;
                case (0xE1): //

                    break;
                case (0xE2): //

                    break;
                case (0xE3): //

                    break;
                case (0xE4): //

                    break;
                case (0xE5): //

                    break;
                case (0xE6): //

                    break;
                case (0xE7): //

                    break;
                case (0xE8): //

                    break;
                case (0xE9): //

                    break;
                case (0xEA): //

                    break;
                case (0xEB): //

                    break;
                case (0xEC): //

                    break;
                case (0xED): //

                    break;
                case (0xEE): //

                    break;
                case (0xEF): //

                    break;
                case (0xF0): //

                    break;
                case (0xF1): //

                    break;
                case (0xF2): //

                    break;
                case (0xF3): //

                    break;
                case (0xF4): //

                    break;
                case (0xF5): //

                    break;
                case (0xF6): //

                    break;
                case (0xF7): //

                    break;
                case (0xF8): //

                    break;
                case (0xF9): //

                    break;
                case (0xFA): //

                    break;
                case (0xFB): //

                    break;
                case (0xFC): //

                    break;
                case (0xFD): //

                    break;
                case (0xFE): //

                    break;
                case (0xFF): //

                    break;
                default:
                    cout << "unimplemented opcode" << endl;
            }
        } else {
            extended_opcode = 0;

            switch(dissassembly){

                case (0x00): //

                    break;
                case (0x01): //

                    break;
                case (0x02): //

                    break;
                case (0x03): //

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
                case (0x10): //

                    break;
                case (0x11): //

                    break;
                case (0x12): //

                    break;
                case (0x13): //

                    break;
                case (0x14): //

                    break;
                case (0x15): //

                    break;
                case (0x16): //

                    break;
                case (0x17): //

                    break;
                case (0x18): //

                    break;
                case (0x19): //

                    break;
                case (0x1A): //

                    break;
                case (0x1B): //

                    break;
                case (0x1C): //

                    break;
                case (0x1D): //

                    break;
                case (0x1E): //

                    break;
                case (0x1F): //

                    break;
                case (0x20): //

                    break;
                case (0x21): //

                    break;
                case (0x22): //

                    break;
                case (0x23): //

                    break;
                case (0x24): //

                    break;
                case (0x25): //

                    break;
                case (0x26): //

                    break;
                case (0x27): //

                    break;
                case (0x28): //

                    break;
                case (0x29): //

                    break;
                case (0x2A): //

                    break;
                case (0x2B): //

                    break;
                case (0x2C): //

                    break;
                case (0x2D): //

                    break;
                case (0x2E): //

                    break;
                case (0x2F): //

                    break;
                case (0x30): //

                    break;
                case (0x31): //

                    break;
                case (0x32): //

                    break;
                case (0x33): //

                    break;
                case (0x34): //

                    break;
                case (0x35): //

                    break;
                case (0x36): //

                    break;
                case (0x37): //

                    break;
                case (0x38): //

                    break;
                case (0x39): //

                    break;
                case (0x3A): //

                    break;
                case (0x3B): //

                    break;
                case (0x3C): //

                    break;
                case (0x3D): //

                    break;
                case (0x3E): //

                    break;
                case (0x3F): //

                    break;
                case (0x40): //

                    break;
                case (0x41): //

                    break;
                case (0x42): //

                    break;
                case (0x43): //

                    break;
                case (0x44): //

                    break;
                case (0x45): //

                    break;
                case (0x46): //

                    break;
                case (0x47): //

                    break;
                case (0x48): //

                    break;
                case (0x49): //

                    break;
                case (0x4A): //

                    break;
                case (0x4B): //

                    break;
                case (0x4C): //

                    break;
                case (0x4D): //

                    break;
                case (0x4E): //

                    break;
                case (0x4F): //

                    break;
                case (0x50): //

                    break;
                case (0x51): //

                    break;
                case (0x52): //

                    break;
                case (0x53): //

                    break;
                case (0x54): //

                    break;
                case (0x55): //

                    break;
                case (0x56): //

                    break;
                case (0x57): //

                    break;
                case (0x58): //

                    break;
                case (0x59): //

                    break;
                case (0x5A): //

                    break;
                case (0x5B): //

                    break;
                case (0x5C): //

                    break;
                case (0x5D): //

                    break;
                case (0x5E): //

                    break;
                case (0x5F): //

                    break;
                case (0x60): //

                    break;
                case (0x61): //

                    break;
                case (0x62): //

                    break;
                case (0x63): //

                    break;
                case (0x64): //l

                    break;
                case (0x65): //

                    break;
                case (0x66): //

                    break;
                case (0x67): //

                    break;
                case (0x68): //

                    break;
                case (0x69): //

                    break;
                case (0x6A): //

                    break;
                case (0x6B): //

                    break;
                case (0x6C): //

                    break;
                case (0x6D): //

                    break;
                case (0x6E): //

                    break;
                case (0x6F): //

                    break;
                case (0x70): //

                    break;
                case (0x71): //

                    break;
                case (0x72): //

                    break;
                case (0x73): //

                    break;
                case (0x74): //

                    break;
                case (0x75): //

                    break;
                case (0x76): //

                    break;
                case (0x77): //

                    break;
                case (0x78): //

                    break;
                case (0x79): //

                    break;
                case (0x7A): //

                    break;
                case (0x7B): //

                    break;
                case (0x7C): //

                    break;
                case (0x7D): //

                    break;
                case (0x7E): //

                    break;
                case (0x7F): //

                    break;
                case (0x80): //

                    break;
                case (0x81): //

                    break;
                case (0x82): //

                    break;
                case (0x83): //

                    break;
                case (0x84): //

                    break;
                case (0x85): //

                    break;
                case (0x86): //

                    break;
                case (0x87): //

                    break;
                case (0x88): //

                    break;
                case (0x89): //

                    break;
                case (0x8A): //

                    break;
                case (0x8B): //

                    break;
                case (0x8C): //

                    break;
                case (0x8D): //

                    break;
                case (0x8E): //

                    break;
                case (0x8F): //

                    break;
                case (0x90): //

                    break;
                case (0x91): //

                    break;
                case (0x92): //

                    break;
                case (0x93): //

                    break;
                case (0x94): //

                    break;
                case (0x95): //

                    break;
                case (0x96): //

                    break;
                case (0x97): //

                    break;
                case (0x98): //

                    break;
                case (0x99): //

                    break;
                case (0x9A): //

                    break;
                case (0x9B): //

                    break;
                case (0x9C): //

                    break;
                case (0x9D): //

                    break;
                case (0x9E): //

                    break;
                case (0x9F): //

                    break;
                case (0xA0): //

                    break;
                case (0xA1): //

                    break;
                case (0xA2): //

                    break;
                case (0xA3): //

                    break;
                case (0xA4): //

                    break;
                case (0xA5): //

                    break;
                case (0xA6): //

                    break;
                case (0xA7): //

                    break;
                case (0xA8): //

                    break;
                case (0xA9): //

                    break;
                case (0xAA): //

                    break;
                case (0xAB): //

                    break;
                case (0xAC): //

                    break;
                case (0xAD): //

                    break;
                case (0xAE): //

                    break;
                case (0xAF): //

                    break;
                case (0xB0): //

                    break;
                case (0xB1): //

                    break;
                case (0xB2): //

                    break;
                case (0xB3): //

                    break;
                case (0xB4): //

                    break;
                case (0xB5): //

                    break;
                case (0xB6): //

                    break;
                case (0xB7): //

                    break;
                case (0xB8): //

                    break;
                case (0xB9): //

                    break;
                case (0xBA): //

                    break;
                case (0xBB): //

                    break;
                case (0xBC): //

                    break;
                case (0xBD): //

                    break;
                case (0xBE): //

                    break;
                case (0xBF): //

                    break;
                case (0xC0): //

                    break;
                case (0xC1): //

                    break;
                case (0xC2): //

                    break;
                case (0xC3): //

                    break;
                case (0xC4): //

                    break;
                case (0xC5): //

                    break;
                case (0xC6): //

                    break;
                case (0xC7): //

                    break;
                case (0xC8): //

                    break;
                case (0xC9): //

                    break;
                case (0xCA): //

                    break;
                case (0xCB): //

                    break;
                case (0xCC): //

                    break;
                case (0xCD): //

                    break;
                case (0xCE): //

                    break;
                case (0xCF): //

                    break;
                case (0xD0): //

                    break;
                case (0xD1): //

                    break;
                case (0xD2): //

                    break;
                case (0xD3): //

                    break;
                case (0xD4): //

                    break;
                case (0xD5): //

                    break;
                case (0xD6): //

                    break;
                case (0xD7): //

                    break;
                case (0xD8): //

                    break;
                case (0xD9): //

                    break;
                case (0xDA): //

                    break;
                case (0xDB): //

                    break;
                case (0xDC): //

                    break;
                case (0xDD): //

                    break;
                case (0xDE): //

                    break;
                case (0xDF): //

                    break;
                case (0xE0): //

                    break;
                case (0xE1): //

                    break;
                case (0xE2): //

                    break;
                case (0xE3): //

                    break;
                case (0xE4): //

                    break;
                case (0xE5): //

                    break;
                case (0xE6): //

                    break;
                case (0xE7): //

                    break;
                case (0xE8): //

                    break;
                case (0xE9): //

                    break;
                case (0xEA): //

                    break;
                case (0xEB): //

                    break;
                case (0xEC): //

                    break;
                case (0xED): //

                    break;
                case (0xEE): //

                    break;
                case (0xEF): //

                    break;
                case (0xF0): //

                    break;
                case (0xF1): //

                    break;
                case (0xF2): //

                    break;
                case (0xF3): //

                    break;
                case (0xF4): //

                    break;
                case (0xF5): //

                    break;
                case (0xF6): //

                    break;
                case (0xF7): //

                    break;
                case (0xF8): //

                    break;
                case (0xF9): //

                    break;
                case (0xFA): //

                    break;
                case (0xFB): //

                    break;
                case (0xFC): //

                    break;
                case (0xFD): //

                    break;
                case (0xFE): //

                    break;
                case (0xFF): //

                    break;

                default:
                    cout << "unimplemented opcode" << endl;
                    break;
            }

        }
    }
}

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