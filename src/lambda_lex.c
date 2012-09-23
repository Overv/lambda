#include <lambda_lex.h>
#include <stdio.h>
#include <stdlib.h>

bool lambda_lex(const char* expr, struct lambda_lex_token** tokens)
{
	struct lambda_lex_state s = {expr, 0, expr[0], expr[1], NULL, NULL};
	struct lambda_lex_token* t = NULL;

	for (;;)
	{
		if (s.first_token == NULL) s.first_token = t;

		switch (s.cur)
		{
		case 0:
			t = lambda_lex_new_token(t);
			t->type = LAMBDA_TOKEN_EOF;
			break;

		case '0': case '1': case '2': case '3':
		case '4': case '5': case '6': case '7':
		case '8': case '9':
			t = lambda_lex_new_token(t);
			t->type = LAMBDA_TOKEN_NUMBER;
			t->value.number = lambda_lex_read_number(&s);
			continue;

		case 'x':
			t = lambda_lex_new_token(t);
			t->type = LAMBDA_TOKEN_VARIABLE;
			break;

		case '+': case '-': case '*': case '/':
			t = lambda_lex_new_token(t);
			t->type = LAMBDA_TOKEN_OPERATOR;
			t->value.op = s.cur;
			break;
		}

		// Update lex state
		s.last_token = t;
		s.prev = s.cur;
		s.cur = s.next;
		s.next = *(s.ptr + 2);
		s.ptr++;

		// Stop when end of expression has been reached
		if (t != NULL && t->type == LAMBDA_TOKEN_EOF)
			break;
	}
	
	*tokens = s.first_token;

	return true;
}

struct lambda_lex_token* lambda_lex_new_token(struct lambda_lex_token* current)
{
	struct lambda_lex_token* t = (struct lambda_lex_token*)malloc(sizeof(struct lambda_lex_token));
	t->type = 0;
	t->value.number = 0;
	t->prev = current;
	t->next = NULL;
	if (current != NULL) current->next = t;
	return t;
}

int lambda_lex_read_number(struct lambda_lex_state* state)
{
	int n = atoi(state->ptr);

	// Move read pointer to end of number
	while (*state->ptr >= '0' && *state->ptr <= '9')
		state->ptr++;

	state->prev = *(state->ptr - 1);
	state->cur = *state->ptr;
	state->next = *(state->ptr + 1);

	return n;
}