#ifndef LAMBDA_ASSEMBLER_HPP
#define LAMBDA_ASSEMBLER_HPP

/*
	Assembler
*/

// Instructions
#define POP 0x8F
#define PUSH 0x50
#define RET 0xC3
#define IMUL_OP1 0x0F
#define IMUL_OP2 0xAF

// Registers
#define EAX 0xC0
#define ECX 0xC1
#define EDX 0xC2
#define EBX 0xC3
#define ESP 0xC4
#define EBP 0xC5
#define ESI 0xC6
#define EDI 0xC7

#endif