#include <lambda_parse.h>

bool lambda_parse(struct lambda_lex_token* tokens)
{
	// Validate input sequence
	if (!lambda_parse_syntax(tokens))
		return false;
	
	// TODO: Optimize expression by simplification

	return true;
}

bool lambda_parse_syntax(struct lambda_lex_token* tokens)
{
	struct lambda_lex_token* token = tokens;

	// Sequence must start with operand
	if (token->type != LAMBDA_TOKEN_NUMBER && token->type != LAMBDA_TOKEN_VARIABLE)
		return false;

	for (;;) {
		// An operator must be surrounded by two operands
		// TODO: Support implicit multiplication, e.g. 3x + 5
		if (token->type == LAMBDA_TOKEN_OPERATOR && (!LAMBDA_IS_OPERAND(token->prev->type) || !LAMBDA_IS_OPERAND(token->next->type)))
			return false;

		// TODO: Support * and /
		if (token->type == LAMBDA_TOKEN_OPERATOR && (token->value.op != '+' && token->value.op != '-'))
			return false;

		if(token->next->type == LAMBDA_TOKEN_EOF)
			break;

		token = token->next;
	}

	// Sequence must end with operand
	if (token->type != LAMBDA_TOKEN_NUMBER && token->type != LAMBDA_TOKEN_VARIABLE)
		return false;

	return true;
}