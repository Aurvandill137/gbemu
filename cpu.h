//
// Created by Ole H. on 12.05.2019.
//

#ifndef GBEMU_CPU_H
#define GBEMU_CPU_H

#define HL (uint16_t)(h << 8 | l)
#define BC (uint16_t)(b << 8 | c)
#define DE (uint16_t)(d << 8 | e)
//Z
#define ZEROFLAG 7
//N
#define SUBTRACTFLAG 6
//H
#define HALFCARRYFLAG 5
//C
#define CARRYFLAG 4

void interpret(uint8_t dissassembly);


#endif //GBEMU_CPU_H
