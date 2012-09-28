#ifndef LAMBDA_LEX_HPP
#define LAMBDA_LEX_HPP

#include <lambda_types.h>

/*
	Lexical analysis
*/

// Lexical tokens
#define LAMBDA_TOKEN_EOF 0
#define LAMBDA_TOKEN_NUMBER 1
#define LAMBDA_TOKEN_OPERATOR 2
#define LAMBDA_TOKEN_VARIABLE 3

#define LAMBDA_IS_OPERAND(t) (t == LAMBDA_TOKEN_NUMBER || t == LAMBDA_TOKEN_VARIABLE)
#define LAMBDA_PRECEDENCE(t) (t->type == LAMBDA_TOKEN_OPERATOR ? ((t->value.op == '+' || t->value.op == '-') ? 1 : 2) : 0)

struct lambda_lex_token {
	int type;
	union value_t {
		int number;
		char op;
	} value;
	struct lambda_lex_token* prev;
	struct lambda_lex_token* next;
};

// Lexical analysis state
struct lambda_lex_state {
	const char* ptr;
	char prev;
	char cur;
	char next;
	struct lambda_lex_token* first_token;
	struct lambda_lex_token* last_token;
};

bool lambda_lex(const char* expr, struct lambda_lex_token** tokens);
void lambda_lex_cleanup(struct lambda_lex_token* tokens);
void lambda_lex_print(struct lambda_lex_token* tokens);

#endif