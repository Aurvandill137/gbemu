//
// Created by Ole H. on 12.05.2019.
//

#include <iostream>
#include "cpu.h"
#include "mmu.h"
#include "opcode_functions.h"
#include "cartridge.h"


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

//Instruction can be 2 bytes so we check if its an extended instruction first
void interpret(uint8_t dissassembly){

    //TODO : add missing opcodes

    if( dissassembly == 0xCB && extended_opcode == 0){
        extended_opcode = 1;
        pc++;

    }else {

        if (extended_opcode == 0) {

            switch (dissassembly) {
                case (0x00): // NOP
                    nop();
                    break;
                case (0x01): // LD BC,d16
                    ld(&b,&c);
                    break;
                case (0x02): // LD (BC),A
                    ld(BC,a);
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
                    ld(&b);
                    break;
                case (0x07): // RLCA
                    rlca();
                    break;
                case (0x08): ////LD (nn),SP

                    break;
                case (0x09): //ADD HL,BC

                    break;
                case (0x0A): //LD A,(BC)
                    ld(&a,BC);
                    break;
                case (0x0B): //DEC BC

                    break;
                case (0x0C): //INC C

                    break;
                case (0x0D): //DEC C

                    break;
                case (0x0E): //LD C,n8
                    ld(&c);
                    break;
                case (0x0F): //RRCA

                    break;
                case (0x10): //STOP

                    break;
                case (0x11): //LD DE,d16

                    break;
                case (0x12): //LD (DE),A
                    ld(DE,a);
                    break;
                case (0x13): //INC DE
                    increment(&d,&e);
                    break;
                case (0x14): //INC D
                    increment(&d);
                    break;
                case (0x15): //DEC D
                    decrement(&d);
                    break;
                case (0x16): //LD D,d8
                    ld(&d);
                    break;
                case (0x17): //RLA

                    break;
                case (0x18): //JR r8

                    break;
                case (0x19): //ADD HL,DE

                    break;
                case (0x1A): //LD A,(DE)
                    ld(&a,DE);
                    break;
                case (0x1B): //DEC DE
                    decrement(&d,&e);
                    break;
                case (0x1C): //INC E
                    increment(&e);
                    break;
                case (0x1D): //DEC E
                    decrement(&e);
                    break;
                case (0x1E): //LD E,d8
                    ld(&e);
                    break;
                case (0x1F): //RRA

                    break;
                case (0x20): //JR NZ,r8

                    break;
                case (0x21): //LD HL,d16
                    ld(&h,&l);
                    break;
                case (0x22): //LD (HL+),A
                    ld(HL+1,a);
                    break;
                case (0x23): //INC HL
                    increment(&h,&l);
                    break;
                case (0x24): //INC H
                    increment(&h);
                    break;
                case (0x25): //DEC H
                    decrement(&h);
                    break;
                case (0x26): //LD H,d8
                    ld(&h);
                    break;
                case (0x27): //DAA

                    break;
                case (0x28): //JR Z,r8

                    break;
                case (0x29): //ADD HL,HL

                    break;
                case (0x2A): //LD A,(HL+)
                    ld(&a,(uint16_t)(HL+1));
                    break;
                case (0x2B): //DEC HL
                    decrement(&h,&l);
                    break;
                case (0x2C): //INC L
                    increment(&l);
                    break;
                case (0x2D): //DEC L
                    decrement(&l);
                    break;
                case (0x2E): //LD L,d8
                    ld(&l);
                    break;
                case (0x2F): //CPL

                    break;
                case (0x30): //JR NC,r8

                    break;
                case (0x31): //LD SP,d16
                    
                    break;
                case (0x32): //LD (HL-),A
                    ld(HL-1,a);
                    break;
                case (0x33): //INC SP
                    increment(&sp);
                    break;
                case (0x34): //INC (HL)
                    increment(HL);
                    break;
                case (0x35): //DEC (HL)
                    decrement(HL);
                    break;
                case (0x36): //LD (HL),d8
                    ld(HL);
                    break;
                case (0x37): //SCF

                    break;
                case (0x38): //JR C,r8

                    break;
                case (0x39): //ADD HL,SP

                    break;
                case (0x3A): //LD A,(HL-)
                    ld(&a,(uint16_t)(HL-1));
                    break;
                case (0x3B): //DEC SP
                    sp--;
                    break;
                case (0x3C): //INC A

                    break;
                case (0x3D): //DEC A

                    break;
                case (0x3E): //LD A,d8
                    ld(&a);
                    break;
                case (0x3F): //CCF

                    break;
                case (0x40): //LD B,B
                    //not necessary to implement
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x41): //LD B,C
                    ld(&b,c);
                    break;
                case (0x42): //LD B,D
                    ld(&b,d);
                    break;
                case (0x43): //LD B,E
                    ld(&b,e);
                    break;
                case (0x44): //LD B,H
                    ld(&b,h);
                    break;
                case (0x45): //LD B,L
                    ld(&b,l);
                    break;
                case (0x46): //LD B,(HL)
                    ld(&b,HL);
                    break;
                case (0x47): //LD B,A
                    ld(&b,a);
                    break;
                case (0x48): //LD C,B
                    ld(&c,b);
                    break;
                case (0x49): //LD C,C
                    // unnecesary to implement
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x4A): //LD C,D
                    ld(&c,d);
                    break;
                case (0x4B): //LD C,E
                    ld(&c,e);
                    break;
                case (0x4C): //LD C,H
                    ld(&c,h);
                    break;
                case (0x4D): //LD C,L
                    ld(&c,l);
                    break;
                case (0x4E): //LD C,(HL)
                    ld(&c,HL);
                    break;
                case (0x4F): //LD C,A
                    ld(&c,a);
                    break;
                case (0x50): //LD D,B
                    ld(&d,b);
                    break;
                case (0x51): //LD D,B
                    ld(&d,c);
                    break;
                case (0x52): //LD D,D
                    //no need to implement
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x53): //LD D,E
                    ld(&d,e);
                    break;
                case (0x54): //LD D,H
                    ld(&d,h);
                    break;
                case (0x55): //LD D,L
                    ld(&d,l);
                    break;
                case (0x56): //LD D,(HL)
                    ld(&d,HL);
                    break;
                case (0x57): //LD D,A
                    ld(&d,a);
                    break;
                case (0x58): //LD E,B
                    ld(&e,b);
                    break;
                case (0x59): //LD E,C
                    ld(&e,c);
                    break;
                case (0x5A): //LD E,D
                    ld(&e,d);
                    break;
                case (0x5B): //LD E,E
                    //no need to implement lel
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x5C): //LD E,H
                    ld(&e,h);
                    break;
                case (0x5D): //LD E,L
                    ld(&e,l);
                    break;
                case (0x5E): //LD E,(HL)
                    ld(&e,HL);
                    break;
                case (0x5F): //LD E,A
                    ld(&e,a);
                    break;
                case (0x60): //ld H,L
                    ld(&h,b);
                    break;
                case (0x61): //ld H,C
                    ld(&h,c);
                    break;
                case (0x62): //ld H,D
                    ld(&h,d);
                    break;
                case (0x63): //ld H,E
                    ld(&h,e);
                    break;
                case (0x64): //ld H,H
                    //no need to implement
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x65): //ld H,L
                    ld(&h,l);
                    break;
                case (0x66): // ld H,(HL)
                    ld(&h,HL);
                    break;
                case (0x67): //ld H,A
                    ld(&h,a);
                    break;
                case (0x68): //ld L,B
                    ld(&l,b);
                    break;
                case (0x69): //ld L,C
                    ld(&l,c);
                    break;
                case (0x6A): //ld L,D
                    ld(&l,d);
                    break;
                case (0x6B): //ld L,E
                    ld(&l,e);
                    break;
                case (0x6C): //ld l,H
                    ld(&l,h);
                    break;
                case (0x6D): //ld L,L
                    //unnecesary to implement
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x6E): //ld L,(HL)
                    ld(&l,HL);
                    break;
                case (0x6F): //ld L,A
                    ld(&l,a);
                    break;
                case (0x70): //1d(HL),B
                    ld(HL,b);
                    break;
                case (0x71): //1d(HL),C
                    ld(HL,c);
                    break;
                case (0x72): //1d(HL),D
                    ld(HL,d);
                    break;
                case (0x73): //1d(HL),E
                    ld(HL,e);
                    break;
                case (0x74): //1d(HL),H
                    ld(HL,h);
                    break;
                case (0x75): //1d(HL),L
                    ld(HL,l);
                    break;
                case (0x76): //HALT
                    halt();
                    break;
                case (0x77): //1d(HL),A
                    ld(HL,a);
                    break;
                case (0x78): //ld A,B
                    ld(&a,b);
                    break;
                case (0x79): //ld A,C
                    ld(&a,c);
                    break;
                case (0x7A): //ld A,D
                    ld(&a,d);
                    break;
                case (0x7B): //ld A,E
                    ld(&a,e);
                    break;
                case (0x7C): //ld A,H
                    ld(&a,h);
                    break;
                case (0x7D): //ld A,L
                    ld(&a,l);
                    break;
                case (0x7E): //ld A,(HL)
                    ld(&a,HL);
                    break;
                case (0x7F): //ld A,A
                    //unnecesary to execute
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x80): //ADD A,B

                    break;
                case (0x81): //ADD A,C

                    break;
                case (0x82): //ADD A,D

                    break;
                case (0x83): //ADD A,E

                    break;
                case (0x84): //ADD A,H

                    break;
                case (0x85): //ADD A,L

                    break;
                case (0x86): //ADD A,(HL)

                    break;
                case (0x87): //ADD A,A

                    break;
                case (0x88): //ADC A,B

                    break;
                case (0x89): //ADC A,C

                    break;
                case (0x8A): //ADC A,D

                    break;
                case (0x8B): //ADC A,E

                    break;
                case (0x8C): //ADC A,H

                    break;
                case (0x8D): //ADC A,L

                    break;
                case (0x8E): //ADC A,(HL)

                    break;
                case (0x8F): //ADC A,A

                    break;
                case (0x90): //SUB B

                    break;
                case (0x91): //SUB C

                    break;
                case (0x92): //SUB D

                    break;
                case (0x93): //SUB E

                    break;
                case (0x94): //SUB H

                    break;
                case (0x95): //SUB L

                    break;
                case (0x96): //SUB (HL)

                    break;
                case (0x97): //SUB A

                    break;
                case (0x98): //SBC A,B

                    break;
                case (0x99): //SBC A,C

                    break;
                case (0x9A): //SBC A,D

                    break;
                case (0x9B): //SBC A,E

                    break;
                case (0x9C): //SBC A,H

                    break;
                case (0x9D): //SBC A,L

                    break;
                case (0x9E): //SBC A,(HL)

                    break;
                case (0x9F): //SBC A,A

                    break;
                case (0xA0): //AND B

                    break;
                case (0xA1): //AND C

                    break;
                case (0xA2): //AND D

                    break;
                case (0xA3): //AND E

                    break;
                case (0xA4): //AND H

                    break;
                case (0xA5): //AND L

                    break;
                case (0xA6): //AND (HL)

                    break;
                case (0xA7): //AND A

                    break;
                case (0xA8): //XOR B

                    break;
                case (0xA9): //XOR C

                    break;
                case (0xAA): //XOR D

                    break;
                case (0xAB): //XOR E

                    break;
                case (0xAC): //XOR H

                    break;
                case (0xAD): //XOR L

                    break;
                case (0xAE): //XOR (HL)

                    break;
                case (0xAF): //XOR A

                    break;
                case (0xB0): //OR B

                    break;
                case (0xB1): //OR C

                    break;
                case (0xB2): //OR D

                    break;
                case (0xB3): //OR E

                    break;
                case (0xB4): //OR H

                    break;
                case (0xB5): //OR L

                    break;
                case (0xB6): //OR (HL)

                    break;
                case (0xB7): //OR A

                    break;
                case (0xB8): //CP B

                    break;
                case (0xB9): //CP C

                    break;
                case (0xBA): //CP D

                    break;
                case (0xBB): //CP E

                    break;
                case (0xBC): //CP H

                    break;
                case (0xBD): //CP L

                    break;
                case (0xBE): //CP (HL)

                    break;
                case (0xBF): //CP A

                    break;
                case (0xC0): //RET NZ

                    break;
                case (0xC1): //POP BC

                    break;
                case (0xC2): //JP NZ,a16

                    break;
                case (0xC3): //JP a16

                    break;
                case (0xC4): //CALL NZ,a16

                    break;
                case (0xC5): //PUSH BC

                    break;
                case (0xC6): //ADD A,d8

                    break;
                case (0xC7): //RST 00H

                    break;
                case (0xC8): //RET Z

                    break;
                case (0xC9): //RET

                    break;
                case (0xCA): //JP Z,a16

                    break;
                case (0xCB): //Prefix CB
                    cout << "this should never happen it should execute an extended opcode" << endl;
                    break;
                case (0xCC): //CALL Z,a16

                    break;
                case (0xCD): //CALL a16

                    break;
                case (0xCE): //ADC A,d8

                    break;
                case (0xCF): //RST 08H

                    break;
                case (0xD0): //RET NC

                    break;
                case (0xD1): //POP DE

                    break;
                case (0xD2): //JP NC,a16

                    break;
                case (0xD3): // -
                    cout << "unused opcode" << endl;
                    break;
                case (0xD4): //CALL NC,a16

                    break;
                case (0xD5): //PUSH DE

                    break;
                case (0xD6): //SUB d8

                    break;
                case (0xD7): //RST 10H

                    break;
                case (0xD8): //RET C

                    break;
                case (0xD9): //RET I

                    break;
                case (0xDA): //JP C,a16

                    break;
                case (0xDB): // -
                    cout << "unused opcode" << endl;
                    break;
                case (0xDC): //CALL C,a16

                    break;
                case (0xDD): // -
                    cout << "unused opcode" << endl;
                    break;
                case (0xDE): //SBC A,d8

                    break;
                case (0xDF): //RST 18H

                    break;
                case (0xE0): //LDH (a8),A

                    break;
                case (0xE1): //POP HL

                    break;
                case (0xE2): //LD (C),A

                    break;
                case (0xE3): //-
                    cout << "unused opcode" << endl;
                    break;
                case (0xE4): //-
                    cout << "unused opcode" << endl;
                    break;
                case (0xE5): //PUSH HL

                    break;
                case (0xE6): //AND d8

                    break;
                case (0xE7): //RST 20H

                    break;
                case (0xE8): //ADD SP,r8

                    break;
                case (0xE9): //JP (HL)

                    break;
                case (0xEA): //LD (a16),A

                    break;
                case (0xEB): //-
                    cout << "unused opcode" << endl;
                    break;
                case (0xEC): //-
                    cout << "unused opcode" << endl;
                    break;
                case (0xED): //-
                    cout << "unused opcode" << endl;
                    break;
                case (0xEE): //XOR d8

                    break;
                case (0xEF): //RST 28H

                    break;
                case (0xF0): //LDH A,(a8)

                    break;
                case (0xF1): //pop AF

                    break;
                case (0xF2): //LD A,(C)

                    break;
                case (0xF3): //DI

                    break;
                case (0xF4): // -
                    cout << "unused opcode" << endl;
                    break;
                case (0xF5): //PUSH AF

                    break;
                case (0xF6): //OR d8

                    break;
                case (0xF7): // RST 30H

                    break;
                case (0xF8): //LD HL,SP+r8

                    break;
                case (0xF9): // LD SP,HL

                    break;
                case (0xFA): // LD A,(a16)

                    break;
                case (0xFB): // EI

                    break;
                case (0xFC): // -
                    cout << "unused opcode" << endl;
                    break;
                case (0xFD): // -
                    cout << "unused opcode" << endl;
                    break;
                case (0xFE): // CP d8

                    break;
                case (0xFF): // RST 38H

                    break;
                default:
                    cout << "unimplemented opcode" << endl;
            }
        } else {
            extended_opcode = 0;

            switch(dissassembly){

                case (0x00): //RLC B

                    break;
                case (0x01): //RLC C

                    break;
                case (0x02): //RLC D

                    break;
                case (0x03): //RLC E

                    break;
                case (0x04): //RLC H

                    break;
                case (0x05): //RLC L

                    break;
                case (0x06): //RLC (HL)

                    break;
                case (0x07): //RLC A

                    break;
                case (0x08): //RRC B

                    break;
                case (0x09): //RRC C

                    break;
                case (0x0A): //RRC D

                    break;
                case (0x0B): //RRC E

                    break;
                case (0x0C): //RRC H

                    break;
                case (0x0D): //RRC L

                    break;
                case (0x0E): //RRC (HL)

                    break;
                case (0x0F): //RRC A

                    break;
                case (0x10): //RL B

                    break;
                case (0x11): //RL C

                    break;
                case (0x12): //RL D

                    break;
                case (0x13): //RL E

                    break;
                case (0x14): //RL H

                    break;
                case (0x15): //RL L

                    break;
                case (0x16): //RL (HL)

                    break;
                case (0x17): //RL A

                    break;
                case (0x18): //RR B

                    break;
                case (0x19): //RR C

                    break;
                case (0x1A): //RR D

                    break;
                case (0x1B): //RR E

                    break;
                case (0x1C): //RR H

                    break;
                case (0x1D): //RR L

                    break;
                case (0x1E): //RR (HL)

                    break;
                case (0x1F): //RR A

                    break;
                case (0x20): //SLA B

                    break;
                case (0x21): //SLA C

                    break;
                case (0x22): //SLA D

                    break;
                case (0x23): //SLA E

                    break;
                case (0x24): //SLA H

                    break;
                case (0x25): //SLA L

                    break;
                case (0x26): //SLA (HL)

                    break;
                case (0x27): //SLA A

                    break;
                case (0x28): //SRA B

                    break;
                case (0x29): //SRA C

                    break;
                case (0x2A): //SRA D

                    break;
                case (0x2B): //SRA E

                    break;
                case (0x2C): //SRA H

                    break;
                case (0x2D): //SRA L

                    break;
                case (0x2E): //SRA (HL)

                    break;
                case (0x2F): //SRA A

                    break;
                case (0x30): //SWAP B
                    swap(&b);
                    break;
                case (0x31): //SWAP C
                    swap(&c);
                    break;
                case (0x32): //SWAP D
                    swap(&d);
                    break;
                case (0x33): //SWAP E
                    swap(&e);
                    break;
                case (0x34): //SWAP H
                    swap(&h);
                    break;
                case (0x35): //SWAP L
                    swap(&l);
                    break;
                case (0x36): //SWAP (HL)
                    swap(HL);
                    break;
                case (0x37): //SWAP A
                    swap(&a);
                    break;
                case (0x38): //SRL B

                    break;
                case (0x39): //SRL C

                    break;
                case (0x3A): //SRL D

                    break;
                case (0x3B): //SRL E

                    break;
                case (0x3C): //SRL H

                    break;
                case (0x3D): //SRL L

                    break;
                case (0x3E): //SRL (HL)

                    break;
                case (0x3F): //SRL A

                    break;
                case (0x40): //BIT 0,B
                    bit(0,&b);
                    break;
                case (0x41): //BIT 0,C
                    bit(0,&c);
                    break;
                case (0x42): //BIT 0,D
                    bit(0,&d);
                    break;
                case (0x43): //BIT 0,E
                    bit(0,&e);
                    break;
                case (0x44): //BIT 0,H
                    bit(0,&h);
                    break;
                case (0x45): //BIT 0,L
                    bit(0,&l);
                    break;
                case (0x46): //BIT 0,(HL)
                    bit(0,HL);
                    break;
                case (0x47): //BIT 0,A
                    bit(0,&a);
                    break;
                case (0x48): //BIT 0,B
                    bit(1,&b);
                    break;
                case (0x49): //BIT 1,C
                    bit(1,&c);
                    break;
                case (0x4A): //BIT 1,D
                    bit(1,&d);
                    break;
                case (0x4B): //BIT 1,E
                    bit(1,&e);
                    break;
                case (0x4C): //BIT 1,H
                    bit(1,&h);
                    break;
                case (0x4D): //BIT 1,L
                    bit(1,&l);
                    break;
                case (0x4E): //BIT 1,(HL)
                    bit(1,HL);
                    break;
                case (0x4F): //BIT 1,A
                    bit(1,&a);
                    break;
                case (0x50): //BIT 2,B
                    bit(2,&b);
                    break;
                case (0x51): //BIT 2,C
                    bit(2,&c);
                    break;
                case (0x52): //BIT 2,D
                    bit(2,&d);
                    break;
                case (0x53): //BIT 2,E
                    bit(2,&e);
                    break;
                case (0x54): //BIT 2,H
                    bit(2,&h);
                    break;
                case (0x55): //BIT 2,L
                    bit(2,&l);
                    break;
                case (0x56): //BIT 2,(HL)
                    bit(2,HL);
                    break;
                case (0x57): //BIT 2,A
                    bit(2,&a);
                    break;
                case (0x58): //BIT 3,B
                    bit(3,&b);
                    break;
                case (0x59): //BIT 3,C
                    bit(3,&c);
                    break;
                case (0x5A): //BIT 3,D
                    bit(3,&d);
                    break;
                case (0x5B): //BIT 3,E
                    bit(3,&e);
                    break;
                case (0x5C): //BIT 3,H
                    bit(3,&h);
                    break;
                case (0x5D): //BIT 3,L
                    bit(3,&l);
                    break;
                case (0x5E): //BIT 3,(HL)
                    bit(3,HL);
                    break;
                case (0x5F): //BIT 3,A
                    bit(3,&a);
                    break;
                case (0x60): //BIT 4,B
                    bit(4,&b);
                    break;
                case (0x61): //BIT 4,C
                    bit(4,&c);
                    break;
                case (0x62): //BIT 4,D
                    bit(4,&d);
                    break;
                case (0x63): //BIT 4,E
                    bit(4,&e);
                    break;
                case (0x64): //BIT 4,H
                    bit(4,&h);
                    break;
                case (0x65): //BIT 4,L
                    bit(4,&l);
                    break;
                case (0x66): //BIT 4,(HL)
                    bit(4,HL);
                    break;
                case (0x67): //BIT 4,A
                    bit(4,&a);
                    break;
                case (0x68): //BIT 5,B
                    bit(5,&b);
                    break;
                case (0x69): //BIT 5,C
                    bit(5,&c);
                    break;
                case (0x6A): //BIT 5,D
                    bit(5,&d);
                    break;
                case (0x6B): //BIT 5,E
                    bit(5,&e);
                    break;
                case (0x6C): //BIT 5,H
                    bit(5,&h);
                    break;
                case (0x6D): //BIT 5,L
                    bit(5,&l);
                    break;
                case (0x6E): //BIT 5,(HL)
                    bit(5,HL);
                    break;
                case (0x6F): //BIT 5,A
                    bit(5,&a);
                    break;
                case (0x70): //BIT 6,B
                    bit(6,&b);
                    break;
                case (0x71): //BIT 6,C
                    bit(6,&c);
                    break;
                case (0x72): //BIT 6,D
                    bit(6,&d);
                    break;
                case (0x73): //BIT 6,E
                    bit(6,&e);
                    break;
                case (0x74): //BIT 6,H
                    bit(6,&h);
                    break;
                case (0x75): //BIT 6,L
                    bit(6,&l);
                    break;
                case (0x76): //BIT 6,(HL)
                    bit(6,HL);
                    break;
                case (0x77): //BIT 6,A
                    bit(6,&a);
                    break;
                case (0x78): //BIT 7,B
                    bit(7,&b);
                    break;
                case (0x79): //BIT 7,C
                    bit(7,&c);
                    break;
                case (0x7A): //BIT 7,D
                    bit(7,&d);
                    break;
                case (0x7B): //BIT 7,E
                    bit(7,&e);
                    break;
                case (0x7C): //BIT 7,H
                    bit(7,&h);
                    break;
                case (0x7D): //BIT 7,L
                    bit(7,&l);
                    break;
                case (0x7E): //BIT 7,(HL)
                    bit(7,HL);
                    break;
                case (0x7F): //BIT 7,A
                    bit(7,&a);
                    break;
                case (0x80): //RES 0,B
                    res(0,&b);
                    break;
                case (0x81): //RES 0,C
                    res(0,&c);
                    break;
                case (0x82): //RES 0,D
                    res(0,&d);
                    break;
                case (0x83): //RES 0,E
                    res(0,&e);
                    break;
                case (0x84): //RES 0,H
                    res(0,&h);
                    break;
                case (0x85): //RES 0,L
                    res(0,&l);
                    break;
                case (0x86): //RES 0,(HL)
                    res(0,HL);
                    break;
                case (0x87): //RES 0,A
                    res(0,&a);
                    break;
                case (0x88): //RES 1,B
                    res(1,&b);
                    break;
                case (0x89): //RES 1,C
                    res(1,&c);
                    break;
                case (0x8A): //RES 1,D
                    res(1,&d);
                    break;
                case (0x8B): //RES 1,E
                    res(1,&e);
                    break;
                case (0x8C): //RES 1,H
                    res(1,&h);
                    break;
                case (0x8D): //RES 1,L
                    res(1,&l);
                    break;
                case (0x8E): //RES 1,(HL)
                    res(1,HL);
                    break;
                case (0x8F): //RES 1,A
                    res(1,&a);
                    break;
                case (0x90): //RES 2,B
                    res(2,&b);
                    break;
                case (0x91): //RES 2,C
                    res(2,&c);
                    break;
                case (0x92): //RES 2,D
                    res(2,&d);
                    break;
                case (0x93): //RES 2,E
                    res(2,&e);
                    break;
                case (0x94): //RES 2,H
                    res(2,&h);
                    break;
                case (0x95): //RES 2,L
                    res(2,&l);
                    break;
                case (0x96): //RES 2,(HL)
                    res(2,HL);
                    break;
                case (0x97): //RES 2,A
                    res(2,&a);
                    break;
                case (0x98): //RES 3,B
                    res(3,&b);
                    break;
                case (0x99): //RES 3,C
                    res(3,&c);
                    break;
                case (0x9A): //RES 3,D
                    res(3,&d);
                    break;
                case (0x9B): //RES 3,E
                    res(3,&e);
                    break;
                case (0x9C): //RES 3,H
                    res(3,&h);
                    break;
                case (0x9D): //RES 3,L
                    res(3,&l);
                    break;
                case (0x9E): //RES 3,(HL)
                    res(3,HL);
                    break;
                case (0x9F): //RES 3,A
                    res(3,&a);
                    break;
                case (0xA0): //RES 4,B
                    res(4,&b);
                    break;
                case (0xA1): //RES 4,C
                    res(4,&c);
                    break;
                case (0xA2): //RES 4,D
                    res(4,&d);
                    break;
                case (0xA3): //RES 4,E
                    res(4,&e);
                    break;
                case (0xA4): //RES 4,H
                    res(4,&h);
                    break;
                case (0xA5): //RES 4,L
                    res(4,&l);
                    break;
                case (0xA6): //RES 4,(HL)
                    res(4,HL);
                    break;
                case (0xA7): //RES 4,A
                    res(4,&a);
                    break;
                case (0xA8): //RES 5,B
                    res(5,&b);
                    break;
                case (0xA9): //RES 5,C
                    res(5,&c);
                    break;
                case (0xAA): //RES 5,D
                    res(5,&d);
                    break;
                case (0xAB): //RES 5,E
                    res(5,&e);
                    break;
                case (0xAC): //RES 5,H
                    res(5,&h);
                    break;
                case (0xAD): //RES 5,L
                    res(5,&l);
                    break;
                case (0xAE): //RES 5,(HL)
                    res(5,HL);
                    break;
                case (0xAF): //RES 5,A
                    res(5,&a);
                    break;
                case (0xB0): //RES 6,B
                    res(6,&b);
                    break;
                case (0xB1): //RES 6,C
                    res(6,&c);
                    break;
                case (0xB2): //RES 6,D
                    res(6,&d);
                    break;
                case (0xB3): //RES 6,E
                    res(6,&e);
                    break;
                case (0xB4): //RES 6,H
                    res(6,&h);
                    break;
                case (0xB5): //RES 6,L
                    res(6,&l);
                    break;
                case (0xB6): //RES 6,(HL)
                    res(6,HL);
                    break;
                case (0xB7): //RES 6,A
                    res(6,&a);
                    break;
                case (0xB8): //RES 7,B
                    res(7,&b);
                    break;
                case (0xB9): //RES 7,C
                    res(7,&c);
                    break;
                case (0xBA): //RES 7,D
                    res(7,&d);
                    break;
                case (0xBB): //RES 7,E
                    res(7,&e);
                    break;
                case (0xBC): //RES 7,H
                    res(7,&h);
                    break;
                case (0xBD): //RES 7,L
                    res(7,&l);
                    break;
                case (0xBE): //RES 7,(HL)
                    res(7,HL);
                    break;
                case (0xBF): //RES 7,A
                    res(7,&a);
                    break;
                case (0xC0): //SET 0,B
                    set(0,&b);
                    break;
                case (0xC1): //SET 0,C
                    set(0,&c);
                    break;
                case (0xC2): //SET 0,D
                    set(0,&d);
                    break;
                case (0xC3): //SET 0,E
                    set(0,&e);
                    break;
                case (0xC4): //SET 0,H
                    set(0,&h);
                    break;
                case (0xC5): //SET 0,L
                    set(0,&l);
                    break;
                case (0xC6): //SET 0,(HL)
                    set(0,HL);
                    break;
                case (0xC7): //SET 0,A
                    set(0,&a);
                    break;
                case (0xC8): //SET 1,B
                    set(1,&b);
                    break;
                case (0xC9): //SET 1,C
                    set(1,&c);
                    break;
                case (0xCA): //SET 1,D
                    set(1,&d);
                    break;
                case (0xCB): //SET 1,E
                    set(1,&e);
                    break;
                case (0xCC): //SET 1,H
                    set(1,&h);
                    break;
                case (0xCD): //SET 1,L
                    set(1,&l);
                    break;
                case (0xCE): //SET 1,(HL)
                    set(1,HL);
                    break;
                case (0xCF): //SET 1,A
                    set(1,&a);
                    break;
                case (0xD0): //SET 2,B
                    set(2,&b);
                    break;
                case (0xD1): //SET 2,C
                    set(2,&c);
                    break;
                case (0xD2): //SET 2,D
                    set(2,&d);
                    break;
                case (0xD3): //SET 2,E
                    set(2,&e);
                    break;
                case (0xD4): //SET 2,H
                    set(2,&h);
                    break;
                case (0xD5): //SET 2,L
                    set(2,&l);
                    break;
                case (0xD6): //SET 2,(HL)
                    set(2,HL);
                    break;
                case (0xD7): //SET 2,A
                    set(2,&a);
                    break;
                case (0xD8): //SET 3,B
                    set(3,&b);
                    break;
                case (0xD9): //SET 3,C
                    set(3,&c);
                    break;
                case (0xDA): //SET 3,D
                    set(3,&d);
                    break;
                case (0xDB): //SET 3,E
                    set(3,&e);
                    break;
                case (0xDC): //SET 3,H
                    set(3,&h);
                    break;
                case (0xDD): //SET 3,L
                    set(3,&l);
                    break;
                case (0xDE): //SET 3,(HL)
                    set(3,HL);
                    break;
                case (0xDF): //SET 3,A
                    set(3,&a);
                    break;
                case (0xE0): //SET 4,B
                    set(4,&b);
                    break;
                case (0xE1): //SET 4,C
                    set(4,&c);
                    break;
                case (0xE2): //SET 4,D
                    set(4,&d);
                    break;
                case (0xE3): //SET 4,E
                    set(4,&e);
                    break;
                case (0xE4): //SET 4,H
                    set(4,&h);
                    break;
                case (0xE5): //SET 4,L
                    set(4,&l);
                    break;
                case (0xE6): //SET 4,(HL)
                    set(4,HL);
                    break;
                case (0xE7): //SET 4,A
                    set(4,&a);
                    break;
                case (0xE8): //SET 5,B
                    set(5,&b);
                    break;
                case (0xE9): //SET 5,C
                    set(5,&c);
                    break;
                case (0xEA): //SET 5,D
                    set(5,&d);
                    break;
                case (0xEB): //SET 5,E
                    set(5,&e);
                    break;
                case (0xEC): //SET 5,H
                    set(5,&h);
                    break;
                case (0xED): //SET 5,L
                    set(5,&l);
                    break;
                case (0xEE): //SET 5,(HL)
                    set(5,HL);
                    break;
                case (0xEF): //SET 5,A
                    set(5,&a);
                    break;
                case (0xF0): //SET 6,B
                    set(6,&b);
                    break;
                case (0xF1): //SET 6,C
                    set(6,&c);
                    break;
                case (0xF2): //SET 6,D
                    set(6,&d);
                    break;
                case (0xF3): //SET 6,E
                    set(6,&e);
                    break;
                case (0xF4): //SET 6,H
                    set(6,&h);
                    break;
                case (0xF5): //SET 6,L
                    set(6,&l);
                    break;
                case (0xF6): //SET 6,(HL)
                    set(6,HL);
                    break;
                case (0xF7): //SET 6,A
                    set(6,&a);
                    break;
                case (0xF8): //SET 7,B
                    set(7,&b);
                    break;
                case (0xF9): //SET 7,C
                    set(7,&c);
                    break;
                case (0xFA): //SET 7,D
                    set(7,&d);
                    break;
                case (0xFB): //SET 7,E
                    set(7,&e);
                    break;
                case (0xFC): //SET 7,H
                    set(7,&h);
                    break;
                case (0xFD): //SET 7,L
                    set(7,&l);
                    break;
                case (0xFE): //SET 7,(HL)
                    set(7,HL);
                    break;
                case (0xFF): //SET 7,A
                    set(7,&a);
                    break;

                default:
                    cout << "unimplemented extended opcode" << endl;
                    break;
            }

        }
    }
}