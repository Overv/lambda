#include <lambda_compile.h>
#include <lambda_asm.h>

// Register layout
// EAX : total
// EBX : variable x
// ECX : immediate

lambda_func lambda_compile_tokens(struct lambda_lex_token* tokens)
{
	lambda_func f;
	struct lambda_asm_state* state = lambda_asm_begin();

	// Preserve registers
	lambda_asm_push(state, LAMBDA_ECX);
	lambda_asm_push(state, LAMBDA_EBX);
	
	// Initialize registers
	lambda_asm_mov_reg(state, LAMBDA_EBX, LAMBDA_REG_PARAM);

	if (tokens->type == LAMBDA_TOKEN_NUMBER)
		lambda_asm_mov_val(state, LAMBDA_EAX, tokens->value.number);
	else
		lambda_asm_mov_reg(state, LAMBDA_EAX, LAMBDA_EBX);

	// Expression
	while (tokens->type != LAMBDA_TOKEN_EOF) {
		if (tokens->type == LAMBDA_TOKEN_OPERATOR) {
			switch (tokens->value.op) {
			case '+':
				if (tokens->next->type == LAMBDA_TOKEN_NUMBER)
					lambda_asm_add_val(state, LAMBDA_EAX, tokens->next->value.number);
				else
					lambda_asm_add_reg(state, LAMBDA_EAX, LAMBDA_EBX);

				break;

			case '-':
				if (tokens->next->type == LAMBDA_TOKEN_NUMBER)
					lambda_asm_sub_val(state, LAMBDA_EAX, tokens->next->value.number);
				else
					lambda_asm_sub_reg(state, LAMBDA_EAX, LAMBDA_EBX);

				break;
			}
		}

		tokens = tokens->next;
	}

	// Restore registers
	lambda_asm_pop(state, LAMBDA_EBX);
	lambda_asm_pop(state, LAMBDA_ECX);

	// Finish
	lambda_asm_ret(state);

	f = lambda_asm_finish(state);

	return f;
}