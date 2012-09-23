#ifndef LAMBDA_ASSEMBLER_HPP
#define LAMBDA_ASSEMBLER_HPP

#include <lambda_types.h>
#include <lambda_lex.h>

/*
	Assembler (x86)
*/

// Instructions
#define POP 0x8F
#define PUSH 0x50
#define RET 0xC3
#define IMUL_OP1 0x0F
#define IMUL_OP2 0xAF
#define MOV 0xC7
#define ADD 0x05
#define SUB 0x2D

// Registers
#define EAX 0xC0
#define ECX 0xC1
#define EDX 0xC2
#define EBX 0xC3
#define ESP 0xC4
#define EBP 0xC5
#define ESI 0xC6
#define EDI 0xC7

lambda_func lambda_asm_test(struct lambda_lex_token* a, char op, struct lambda_lex_token* b);

#endif