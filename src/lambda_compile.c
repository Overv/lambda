#include <lambda_compile.h>
#include <lambda_asm.h>

lambda_func lambda_compile_tokens(struct lambda_lex_token* tokens)
{
	lambda_func f;
	struct lambda_asm_state* state = lambda_asm_begin();

	lambda_asm_mov_reg(state, LAMBDA_EAX, LAMBDA_REG_PARAM);
	lambda_asm_imul_reg(state, LAMBDA_EAX, LAMBDA_EAX);
	lambda_asm_ret(state);

	f = lambda_asm_finish(state);

	return f;
}