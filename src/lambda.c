#include <lambda.h>
#include <lambda_mem.h>
#include <lambda_lex.h>
#include <lambda_parse.h>
#include <lambda_compile.h>

lambda_func lambda_compile(const char* expr)
{
	struct lambda_lex_token* tokens = NULL;
	lambda_func f;

	// Lexical analysis
	if (lambda_lex(expr, &tokens) == false)
		return NULL;

	// Parse tokens and prepare compiler input
	if (lambda_parse(tokens) == false) {
		lambda_lex_cleanup(tokens);
		return NULL;
	}

	// Turn token sequence into instructions
	f = lambda_compile_tokens(tokens);

	// Clean up
	lambda_lex_cleanup(tokens);

	return f;
}

void lambda_cleanup(lambda_func f)
{
	lambda_free(f);
}