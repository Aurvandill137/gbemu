//
// Created by Ole H. on 12.05.2019.
//

#include <iostream>
#include "cpu.h"
#include "mmu.h"

#define HL (h<<8 | l)

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
                    //NOP
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x01): // LD BC,d16
                    b = read_address(pc+1);
                    c = read_address(pc+2);
                    cpu_cycles = 12;
                    pc+=3;
                    break;
                case (0x02): // LD (BC),A
                    write_address(a,(b<<8u|c));
                    cpu_cycles = 8;
                    pc++;
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
                case (0x04): // LD (BC),A

                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x05): // LD (BC),A

                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x06): // LD (BC),A

                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x07): // LD (BC),A

                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x08): // LD (BC),A

                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x09): // LD (BC),A

                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x0A): // LD (BC),A

                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x0B): // LD (BC),A

                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x0C): // LD (BC),A

                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x0D): // LD (BC),A

                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x0E): // LD (BC),A

                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x0F): // LD (BC),A

                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x40): //LD B,B
                    //not necessary to implement
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x41): //LD B,C
                    load(b,c);
                    break;
                case (0x42): //LD B,D
                    load(b,d);
                    break;
                case (0x43): //LD B,E
                    load(b,e);
                    break;
                case (0x44): //LD B,H
                    load(b,h);
                    break;
                case (0x45): //LD B,L
                    load(b,l);
                    break;
                case (0x46): //LD B,((HL)
                    b = read_address(HL);
                    cpu_cycles = 8;
                    pc++;
                    break;
                case (0x47): //r1 = B , r2 = A
                    load(b,a);
                    break;
                case (0x48): //r1 = C , r2 = B
                    load(c,b)
                    break;
                case (0x49): //r1 = C , r2 = C
                    // unnecesary to implement
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x4A): //r1 = C , r2 = D
                    c = d;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x4B): //r1 = C , r2 = E
                    c = e;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x4C): //r1 = C , r2 = H
                    c = h;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x4D): //r1 = C , r2 = L
                    c = l;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x4E): //r1 = C , r2 = HL
                    c = read_address(HL);
                    cpu_cycles = 8;
                    pc++;
                    break;
                case (0x4F): //r1 = C , r2 = A
                    c = a;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x50): //r1 = D , r2 = B
                    d = b;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x51): //r1 = D , r2 = C
                    d = c;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x52): //r1 = D , r2 = D
                    //no need to implement
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x53): //r1 = D , r2 = E
                    d = e;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x54): //r1 = D , r2 = H
                    d = h;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x55): //r1 = D , r2 = L
                    d = l;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x56): //r1 = D , r2 = HL
                    d = read_address(HL);
                    cpu_cycles = 8;
                    pc++;
                    break;
                case (0x57): //r1 = D , r2 = A
                    d = a;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x58): //r1 = E , r2 = B
                    e = b;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x59): //r1 = E , r2 = C
                    e = c;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x5A): //r1 = E , r2 = D
                    e = d;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x5B): //r1 = E , r2 = E
                    //no need to implement lel
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x5C): //r1 = E , r2 = H
                    e = h;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x5D): //r1 = E , r2 = L
                    e = l;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x5E): //r1 = E , r2 = HL
                    e = read_address(HL);
                    cpu_cycles = 8;
                    pc++;
                    break;
                case (0x5F): //r1 = E , r2 = A
                    e = a;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x60): //r1 = H , r2 = B
                    h = b;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x61): //r1 = H , r2 = C
                    h = c;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x62): //r1 = H , r2 = D
                    h = d;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x63): //r1 = H , r2 = E
                    h = e;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x64): //r1 = H , r2 = H
                    //no need to implement
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x65): //r1 = H , r2 = L
                    h = l;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x66): //r1 = H , r2 = HL
                    h = read_address(HL);
                    cpu_cycles = 8;
                    pc++;
                    break;
                case (0x67): //r1 = H , r2 = A
                    h = a;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x68): //r1 = L , r2 = B
                    l = b;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x69): //r1 = L , r2 = C
                    l = c;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x6A): //r1 = L , r2 = D
                    l = d;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x6B): //r1 = L , r2 = E
                    l = e;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x6C): //r1 = L , r2 = H
                    l = h;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x6D): //r1 = L , r2 = L
                    //unnecesary to implement
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x6E): //r1 = L , r2 = HL
                    l = read_address(HL);
                    cpu_cycles = 8;
                    pc++;
                    break;
                case (0x6F): //r1 = L , r2 = A
                    l = a;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x70): //r1 = HL , r2 = B
                    l = b;
                    cpu_cycles = 8;
                    pc++;
                    break;
                case (0x71): //r1 = A , r2 = C
                    l = c;
                    cpu_cycles = 8;
                    pc++;
                    break;
                case (0x72): //r1 = HL , r2 = D
                    l = d;
                    cpu_cycles = 8;
                    pc++;
                    break;
                case (0x73): //r1 = HL , r2 = E
                    l = e;
                    cpu_cycles = 8;
                    pc++;
                    break;
                case (0x74): //r1 = (HL) , r2 = H
                    l = h;
                    cpu_cycles = 8;
                    pc++;
                    break;
                case (0x75): //r1 = HL , r2 = L

                    cpu_cycles = 8;
                    pc++;
                    break;
                case (0x76): //HALT
                    //wait for an idea to implement lol
                    pc++;
                    break;
                case (0x77): //r1 = HL , r2 = A
                    l = a;
                    cpu_cycles = 4;
                    pc++;
                    break;
                case (0x78): //r1 = A , r2 = B
                    load(a,b);
                    break;
                case (0x79): //r1 = A , r2 = C
                    load(a,c);
                    break;
                case (0x7A): //r1 = A , r2 = D
                    load(a,d);
                    break;
                case (0x7B): //r1 = A , r2 = E
                    load(a,e);
                    break;
                case (0x7C): //r1 = A , r2 = H
                    load(a,h);
                    break;
                case (0x7D): //r1 = A , r2 = L
                    load(a,l);
                    break;
                case (0x7E): //r1 = A , r2 = HL
                    a = read_address(HL);
                    cpu_cycles = 8;
                    pc++;
                    break;
                case (0x7F): //r1 = A , r2 = A
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

void load(uint8_t a, uint8_t b){

    a = b;
    cpu_cycles = 4;
    pc++;

}
void load_to_mem(uint16_t address, uint8_t data){
    write_address(data, address);


}
void load_from_mem(uint8_t* reg, uint16_t address){


}