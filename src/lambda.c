#include <lambda.h>
#include <lambda_mem.h>
#include <lambda_lex.h>
#include <lambda_asm.h>

lambda_func lambda_compile(const char* expr)
{
	struct lambda_lex_token* tokens = NULL;
	lambda_func f;

	// Lexical analysis
	if (lambda_lex(expr, &tokens) == 0)
		return NULL;

	// Generate code
	// TODO: Support more than just constant[+-*/]constant by writing a real parser/compiler/assembler
	if (tokens->type != LAMBDA_TOKEN_NUMBER || tokens->next->type != LAMBDA_TOKEN_OPERATOR ||
		tokens->next->next->type != LAMBDA_TOKEN_NUMBER || tokens->next->next->next->type != LAMBDA_TOKEN_EOF)
		return NULL;

	f = lambda_asm_test(tokens->value.number, tokens->next->value.op, tokens->next->next->value.number);

	// Clean up
	lambda_lex_cleanup(tokens);

	return f;
}

void lambda_cleanup(lambda_func f)
{
	lambda_free(f);
}