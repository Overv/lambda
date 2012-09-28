#include <lambda_parse.h>
#include <stdlib.h>

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
	struct lambda_lex_token* temp;

	// Sequence must start with operand
	if (token->type != LAMBDA_TOKEN_NUMBER && token->type != LAMBDA_TOKEN_VARIABLE)
		return false;

	for (;;) {
		// An operator must be surrounded by two operands
		if (token->type == LAMBDA_TOKEN_OPERATOR && (!LAMBDA_IS_OPERAND(token->prev) || !LAMBDA_IS_OPERAND(token->next)))
			return false;

		// A combination like x2 is not valid
		if (token->type == LAMBDA_TOKEN_VARIABLE && token->next->type == LAMBDA_TOKEN_NUMBER)
			return false;

		// Implicit multiplication (e.g. 2x -> 2 * x or xx -> x * x)
		if (LAMBDA_IS_OPERAND(token) && token->next->type == LAMBDA_TOKEN_VARIABLE) {
			temp = token->next;
			token->next = (struct lambda_lex_token*)malloc(sizeof(struct lambda_lex_token));
			token->next->type = LAMBDA_TOKEN_OPERATOR;
			token->next->value.op = '*';
			token->next->prev = token;
			token->next->next = temp;
			temp->prev = token->next;
		}

		if(token->next->type == LAMBDA_TOKEN_EOF)
			break;

		token = token->next;
	}

	// Sequence must end with operand
	if (token->type != LAMBDA_TOKEN_NUMBER && token->type != LAMBDA_TOKEN_VARIABLE)
		return false;

	return true;
}