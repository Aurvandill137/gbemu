//
// Created by Ole H. on 12.05.2019.
//

#ifndef GBEMU_CPU_H
#define GBEMU_CPU_H

#define HL (h << 8 | l)
#define BC (b << 8 | c)
#define ZEROFLAG 7
#define SUBTRACTFLAG 6
#define HALFCARRYFLAG 5
#define CARRYFLAG 4

void interpret(uint8_t dissassembly);


#endif //GBEMU_CPU_H
