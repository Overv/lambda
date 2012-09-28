#include <lambda_compile.h>
#include <lambda_asm.h>

// Register layout
// ESI : total
// EDI : variable x
// EDX:EAX, EBX : immediate (EDX and EBX only for division)

void lambda_compile_mov_token(struct lambda_asm_state* state, int reg, struct lambda_lex_token* value);

lambda_func lambda_compile_tokens(struct lambda_lex_token* tokens)
{
	lambda_func f;
	struct lambda_asm_state* state = lambda_asm_begin();
	int pLevel = 0; // Operator precedence level

	// Preserve registers
	lambda_asm_push(state, LAMBDA_ESI);
	lambda_asm_push(state, LAMBDA_EDI);
	lambda_asm_push(state, LAMBDA_EBX);
	
	// Initialize registers
	if (LAMBDA_REG_PARAM != LAMBDA_EDI)
		lambda_asm_mov_reg(state, LAMBDA_EDI, LAMBDA_REG_PARAM);
	lambda_asm_mov_val(state, LAMBDA_ESI, 0);

	// Walk through expression
	while (tokens->type != LAMBDA_TOKEN_EOF) {
		if (tokens->type == LAMBDA_TOKEN_OPERATOR) {
			switch (tokens->value.op) {
			case '+':
				if (pLevel < 1)
					lambda_compile_mov_token(state, LAMBDA_ESI, tokens->prev);
				else if (pLevel > 1)
					lambda_asm_add_reg(state, LAMBDA_ESI, LAMBDA_EAX);
				pLevel = 1;

				// Only add this value if there is no operator with a higher predence coming up
				if (LAMBDA_PRECEDENCE(tokens->next->next) <= 1) {
					if (tokens->next->type == LAMBDA_TOKEN_NUMBER)
						lambda_asm_add_val(state, LAMBDA_ESI, tokens->next->value.number);
					else
						lambda_asm_add_reg(state, LAMBDA_ESI, LAMBDA_EDI);
				}

				break;

			case '-':
				if (pLevel < 1)
					lambda_compile_mov_token(state, LAMBDA_ESI, tokens->prev);
				else if (pLevel > 1)
					lambda_asm_add_reg(state, LAMBDA_ESI, LAMBDA_EAX);
				pLevel = 1;
				
				// Only subtract this value if there is no operator with a higher predence coming up
				if (LAMBDA_PRECEDENCE(tokens->next->next) <= 1) {
					if (tokens->next->type == LAMBDA_TOKEN_NUMBER)
						lambda_asm_sub_val(state, LAMBDA_ESI, tokens->next->value.number);
					else
						lambda_asm_sub_reg(state, LAMBDA_ESI, LAMBDA_EDI);
				} else {
					// Next number in higher precedence operation is made negative as a result of this subtraction
					tokens->next->value.number *= -1;
				}

				break;

			case '*':
				if (pLevel < 2) {
					lambda_asm_mov_val(state, LAMBDA_EDX, 0);
					lambda_compile_mov_token(state, LAMBDA_EAX, tokens->prev);
					pLevel = 2;
				}

				if (tokens->next->type == LAMBDA_TOKEN_NUMBER)
					lambda_asm_imul_val(state, LAMBDA_EAX, LAMBDA_EAX, tokens->next->value.number);
				else
					lambda_asm_imul_reg(state, LAMBDA_EAX, LAMBDA_EDI);

				break;

			case '/':
				if (pLevel < 2) {
					lambda_asm_mov_val(state, LAMBDA_EDX, 0);
					lambda_compile_mov_token(state, LAMBDA_EAX, tokens->prev);
					pLevel = 2;
				}

				if (tokens->next->type == LAMBDA_TOKEN_NUMBER) {
					lambda_asm_mov_val(state, LAMBDA_EBX, tokens->next->value.number);
					lambda_asm_idiv(state, LAMBDA_EBX);
				} else
					lambda_asm_idiv(state, LAMBDA_EDI);

				break;
			}
		}

		tokens = tokens->next;
	}

	// If expression finished at multiplication/division level, add it to total sum
	if (pLevel > 1)
		lambda_asm_add_reg(state, LAMBDA_ESI, LAMBDA_EAX);

	lambda_asm_mov_reg(state, LAMBDA_EAX, LAMBDA_ESI);

	// Restore registers
	lambda_asm_pop(state, LAMBDA_EBX);
	lambda_asm_pop(state, LAMBDA_EDI);
	lambda_asm_pop(state, LAMBDA_ESI);

	// Finish
	lambda_asm_ret(state);

	f = lambda_asm_finish(state);

	return f;
}

void lambda_compile_mov_token(struct lambda_asm_state* state, int reg, struct lambda_lex_token* value)
{
	if (value->type == LAMBDA_TOKEN_NUMBER)
		lambda_asm_mov_val(state, reg, value->value.number);
	else
		lambda_asm_mov_reg(state, reg, LAMBDA_EDI);
}