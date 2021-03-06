#ifndef LAMBDA_ASSEMBLER_HPP
#define LAMBDA_ASSEMBLER_HPP

#include <lambda_types.h>

/*
	Assembler (x86)
*/

// Registers
#define LAMBDA_EAX 0
#define LAMBDA_ECX 1
#define LAMBDA_EDX 2
#define LAMBDA_EBX 3
#define LAMBDA_ESP 4
#define LAMBDA_EBP 5
#define LAMBDA_ESI 6
#define LAMBDA_EDI 7

// Instructions
#define LAMBDA_MOV_REG 0x8B
#define LAMBDA_MOV_VAL 0xC7
#define LAMBDA_POP 0x8F
#define LAMBDA_PUSH 0xFF
#define LAMBDA_ADD_REG 0x01
#define LAMBDA_SUB_REG 0x29
#define LAMBDA_ADDSUB_VAL 0x81
#define LAMBDA_IMUL_REG_1 0x0F
#define LAMBDA_IMUL_REG_2 0xAF
#define LAMBDA_IMUL_VAL 0x69
#define LAMBDA_IDIV 0xF7
#define LAMBDA_RET 0xC3

// Addressing modes
#define LAMBDA_MOD_REG (3 << 6)

// Assembler state
struct lambda_asm_state {
	uchar* buffer;
	int size;
	int off;
};

struct lambda_asm_state* lambda_asm_begin();
lambda_func lambda_asm_finish(struct lambda_asm_state* state);

void lambda_asm_mov_reg(struct lambda_asm_state* state, int dest, int src);
void lambda_asm_mov_val(struct lambda_asm_state* state, int dest, int value);

void lambda_asm_pop(struct lambda_asm_state* state, int dest);
void lambda_asm_push(struct lambda_asm_state* state, int src);

void lambda_asm_add_reg(struct lambda_asm_state* state, int dest, int src);
void lambda_asm_add_val(struct lambda_asm_state* state, int dest, int value);

void lambda_asm_sub_reg(struct lambda_asm_state* state, int dest, int src);
void lambda_asm_sub_val(struct lambda_asm_state* state, int dest, int value);

void lambda_asm_imul_reg(struct lambda_asm_state* state, int dest, int src);
void lambda_asm_imul_val(struct lambda_asm_state* state, int dest, int src, int value);

void lambda_asm_idiv(struct lambda_asm_state* state, int divisor);

void lambda_asm_ret(struct lambda_asm_state* state);

#endif