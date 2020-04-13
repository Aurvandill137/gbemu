#ifndef GBEMU_OPCODE_FUNCTIONS_H
#define GBEMU_OPCODE_FUNCTIONS_H

//helpers
void set_flag(uint8_t flag);
void clear_flag(uint8_t flag);

//general
void halt();
void nop();

//LD Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////
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
//LD SP,d16
void ld_sp();
//LD [d16],SP
void ld_sp_to_mem();
//LD HL,SP+d8
void ld_hl_sp_d8();
//LD SP,HL
void ld_sp_hl();


//ALU
////////////////////////////////////////////////////////////////////////////////////////

//ADC A,r8
void alu_adc(uint8_t r8);
//ADC A,[HL]
void alu_adc(uint16_t address);
//ADC A,n8
void alu_adc();
//ADD A,r8
void alu_add(uint8_t r8);
//ADD A,[HL]
void alu_add(uint16_t address);
//ADD A,n8
void alu_add();
//ADD HL,r16
void alu_add_HL(uint16_t r16);
//AND A,r8
void alu_and(uint8_t r8);
//AND A,[HL]
void alu_and(uint16_t address);
//AND A,n8
void alu_and();
//CP A,r8
void alu_cp(uint8_t r8);
//CP A,[HL]
void alu_cp(uint16_t address);
//CP A,n8
void alu_cp();
//OR A,r8
void alu_or(uint8_t r8);
//OR A,[HL]
void alu_or(uint16_t address);
//OR A,n8
void alu_or();
//SBC A,r8
void alu_sbc(uint8_t r8);
//SBC A,[HL]
void alu_sbc(uint16_t address);
//SBC A,n8
void alu_sbc();
//SUB A,r8
void alu_sub(uint8_t r8);
//SUB A,[HL]
void alu_sub(uint16_t address);
//SUB A,n8
void alu_sub();
//XOR A,r8
void alu_xor(uint8_t r8);
//XOR A,[HL]
void alu_xor(uint16_t address);
//XOR A,n8
void alu_xor();




//increment and decrement functions
/////////////////////////////////////////////////////////////////////////////////////////
void increment(uint8_t *var);
void increment(uint8_t *var1, uint8_t *var2);
void increment(uint16_t *sp);
void increment(uint16_t address);
void decrement(uint8_t *var);
void decrement(uint8_t *var, uint8_t *var2);
void decrement(uint16_t *sp);
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