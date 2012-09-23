#include <lambda_asm.h>
#include <lambda_mem.h>

lambda_func lambda_asm_test(int a, char op, int b)
{
	int off;
	uchar* code = (uchar*)lambda_alloc(32, true);

	code[0] = POP;
	code[1] = ECX;
	code[2] = POP;
	code[3] = EAX;

	code[4] = MOV;
	code[5] = EAX;
	*((int*)&code[6]) = a;
	
	if (op == '+') {
		code[10] = ADD;
		*((int*)&code[11]) = b;
		off = 15;
	} else if (op == '-') {
		code[10] = SUB;
		*((int*)&code[11]) = b;
		off = 15;
	} else if (op == '*') {
		code[10] = 0x69;
		code[11] = 0xC0;
		*((int*)&code[12]) = b;
		off = 16;
	} else if (op == '/') {
		code[10] = MOV;
		code[11] = EDX;
		*((int*)&code[12]) = 0;
		code[16] = MOV;
		code[17] = EDI;
		*((int*)&code[18]) = b;
		code[22] = 0xF7;
		code[23] = 0xFF;

		off = 24;
	}

	code[off+0] = PUSH + EAX - EAX;
	code[off+1] = PUSH + ECX - EAX;
	code[off+2] = RET;

	return (lambda_func)code;
}