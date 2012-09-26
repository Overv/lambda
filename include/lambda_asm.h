#ifndef LAMBDA_ASSEMBLER_HPP
#define LAMBDA_ASSEMBLER_HPP

#include <lambda_types.h>

/*
	Assembler (x86)
*/

// Registers
#define EAX 0
#define ECX 1
#define EDX 2
#define EBX 3
#define ESP 4
#define EBP 5
#define ESI 6
#define EDI 7

#ifdef LAMBDA_FASTCALL
#define REG_PARAM ECX
#else
#define REG_PARAM EDI
#endif

// Instructions
#define MOV_REG 0x8B
#define MOV_VAL 0xC7
#define POP 0x8F
#define PUSH 0xFF
#define ADD_REG 0x01
#define SUB_REG 0x29
#define ADDSUB_VAL 0x81
#define IMUL_REG_1 0x0F
#define IMUL_REG_2 0xAF
#define IMUL_VAL 0x69
#define IDIV 0xF7
#define RET 0xC3

// Addressing modes
#define MOD_REG (3 << 6)

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