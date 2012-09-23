#include <lambda_asm.h>
#include <lambda_mem.h>

// This is a code playground, don't worry :-)
lambda_func lambda_asm_test(struct lambda_lex_token* a, char op, struct lambda_lex_token* b)
{
	uchar* code = (uchar*)lambda_alloc(32, true);
	int off;

	code[0] = POP;
	code[1] = ECX;
	code[2] = POP;
	code[3] = EBX;
	
	if (a->type == LAMBDA_TOKEN_NUMBER) {
		code[4] = MOV;
		code[5] = EAX;
		*((int*)&code[6]) = a->value.number;

		off = 10;
	} else {
		// mov eax, ebx
		code[4] = 0x89;
		code[5] = 0xD8;

		off = 4;
	}
	
	if (op == '+') {
		if (b->type == LAMBDA_TOKEN_NUMBER) {
			code[off] = ADD;
			*((int*)&code[off+1]) = b->value.number;

			off = off + 5;
		} else {
			code[off] = 0x03;
			code[off+1] = 0xC3;

			off = off + 2;
		}
	} else if (op == '-') {
		if (b->type == LAMBDA_TOKEN_NUMBER) {
			code[off] = SUB;
			*((int*)&code[off+1]) = b->value.number;

			off = off + 5;
		} else {
			code[off] = 0x2B;
			code[off+1] = 0xC3;

			off = off + 2;
		}
	} else if (op == '*') {
		if (b->type == LAMBDA_TOKEN_NUMBER) {
			code[off] = 0x69;
			code[off+1] = 0xC0;
			*((int*)&code[off+2]) = b->value.number;

			off = off + 6;
		} else {
			code[off] = 0xF7;
			code[off+1] = 0xEB;

			off = off + 2;
		}
	} else if (op == '/') {
		if (b->type == LAMBDA_TOKEN_NUMBER) {
			code[off] = MOV;
			code[off+1] = EDX;
			*((int*)&code[off+2]) = 0;
			code[off+6] = MOV;
			code[off+7] = EDI;
			*((int*)&code[off+8]) = b->value.number;
			code[off+12] = 0xF7;
			code[off+13] = 0xFF;

			off = off + 14;
		} else {
			code[off] = MOV;
			code[off+1] = EDX;
			*((int*)&code[off+2]) = 0;
			code[off+6] = 0xF7;
			code[off+7] = 0xFB;

			off = off + 8;
		}
	}

	code[off+0] = PUSH + EAX - EAX;
	code[off+1] = PUSH + ECX - EAX;
	code[off+2] = RET;

	return (lambda_func)code;
}