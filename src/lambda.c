#include <lambda.h>
#include <lambda_mem.h>
#include <lambda_lex.h>
#include <lambda_asm.h>

lambda_func lambda_compile(const char* expr)
{
	struct lambda_lex_token* tokens = NULL;
	uchar* code;

	// Lexical analysis
	if (lambda_lex(expr, &tokens) == 0)
		return NULL;

	// Generate code
	code = (uchar*)lambda_alloc(16, true);

	code[0] = POP;
	code[1] = ECX;
	code[2] = POP;
	code[3] = EAX;
	code[4] = IMUL_OP1;
	code[5] = IMUL_OP2;
	code[6] = EAX;
	code[7] = PUSH + EAX - EAX;
	code[8] = PUSH + ECX - EAX;
	code[9] = RET;

	// Clean up
	lambda_lex_cleanup(tokens);

	return (lambda_func)code;
}

void lambda_cleanup(lambda_func f)
{
	lambda_free(f);
}