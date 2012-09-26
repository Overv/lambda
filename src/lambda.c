#include <lambda.h>
#include <lambda_mem.h>
#include <lambda_lex.h>
#include <lambda_asm.h>

lambda_func lambda_compile(const char* expr)
{
	struct lambda_lex_token* tokens = NULL;
	struct lambda_asm_state* state;
	lambda_func f;

	// Lexical analysis
	if (lambda_lex(expr, &tokens) == 0)
		return NULL;

	// TODO: Generate real code
	state = lambda_asm_begin();
	lambda_asm_mov_reg(state, EAX, REG_PARAM);
	lambda_asm_imul_reg(state, EAX, EAX);
	lambda_asm_ret(state);
	f = lambda_asm_finish(state);

	// Clean up
	lambda_lex_cleanup(tokens);

	return f;
}

void lambda_cleanup(lambda_func f)
{
	lambda_free(f);
}