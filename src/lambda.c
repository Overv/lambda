#include <lambda.h>
#include <lambda_mem.h>
#include <lambda_lex.h>
#include <string.h>

lambda_func lambda_compile(const char* expr)
{
	struct lambda_lex_token* tokens = NULL;
	uchar* foo;

	// Lexical analysis
	if (lambda_lex(expr, &tokens) == 0)
		return NULL;

	lambda_lex_cleanup(tokens);
	
	// Return dummy function that always returns x squared
	foo = (uchar*)lambda_alloc(8, true);

	foo[0] = 0x59; // pop ecx
	foo[1] = 0x58; // pop eax
	foo[2] = 0x0F; // imul eax, eax
	foo[3] = 0xAF;
	foo[4] = 0xC0;
	foo[5] = 0x50; // push eax
	foo[6] = 0x51; // push ecx
	foo[7] = 0xC3; // ret

	return (lambda_func)foo;
}

void lambda_cleanup(lambda_func f)
{
	lambda_free(f);
}