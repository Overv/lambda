#include <lambda.h>
#include <lambda_lex.h>
#include <string.h>

lambda_func lambda_compile(const char* expr)
{
	struct lambda_lex_token* tokens = NULL;
	uchar* foo;

	// Lexical analysis
	if (lambda_lex(expr, &tokens) == 0)
		return NULL;

	// TODO: Clean up tokens after finishing
	
	// Return dummy function that always returns zero
	foo = (uchar*)lambda_alloc(8, true);

	foo[0] = 0xB8;
	foo[1] = 0x00;
	foo[2] = 0x00;
	foo[3] = 0x00;
	foo[4] = 0x00;
	foo[5] = 0xC3;

	return (lambda_func)foo;
}

void lambda_cleanup(lambda_func f)
{
	lambda_free(f);
}