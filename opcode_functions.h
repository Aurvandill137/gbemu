#ifndef GBEMU_OPCODE_FUNCTIONS_H
#define GBEMU_OPCODE_FUNCTIONS_H

//helpers
void set_flag(uint8_t flag);
void clear_flag(uint8_t flag);

//general
void halt();
void nop();
//LD Functions
//LD r8,r8
void ld(uint8_t *a,uint8_t b);
//LD r8,d8
void ld(uint8_t *a);
//LD r16,d16
void ld(uint8_t *reg1, uint8_t *reg2);
//LD (HL),r8
void ld(uint16_t address,uint8_t b);
//LD (HL),d8
void ld(uint16_t address);
//LD r8,(HL)
void ld(uint8_t *a,uint16_t address);

//LD (r16),a
void ld_a(uint16_t adress);
//LD (d16),A
void ld_a();
//LDH (d16),A
void ldh();
//LDH (C),A
void ldh(uint8_t c);
//LD A,(r16)
void ld_to_a(uint16_t path);
//LD A,(d16)
void ld_to_a();
//LDH A,(d16)
void ldh_to_a();
//LDH A,(C)
void ldh_to_a(uint8_t c);
//LD (HLI),A
void ldi_a();
//LD (HLD),A
void ldd_a();
//LD A,(HLI)
void ldi_to_a();
//LD A,(HLD)
void ldd_to_a();


//increment and decrement functions
void increment(uint8_t *var);
void decrement(uint8_t *var);
void increment(uint8_t *var1, uint8_t *var2);
void increment(uint16_t *sp);
void decrement(uint8_t *var, uint8_t *var2);
void increment(uint16_t address);
void decrement(uint16_t address);

//bit Logic Operations
void swap(uint8_t *var);
void swap(uint16_t address);
void rlc(uint8_t *var);
void rlca(); //basicaly rlc on register A with half the cpu cykles
void res(uint8_t bit, uint8_t *reg);
void res(uint8_t bit, uint16_t address);
void set(uint8_t bit, uint8_t *reg);
void set(uint8_t bit, uint16_t address);
void bit(uint8_t bittest, uint8_t *var);
void bit(uint8_t bittest, uint16_t address);

#endif //GBEMU_OPCODE_FUNCTIONS_H