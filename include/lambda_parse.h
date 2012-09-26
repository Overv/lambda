#ifndef LAMBDA_PARSE_HPP
#define LAMBDA_PARSE_HPP

#include <lambda_types.h>
#include <lambda_lex.h>

/*
	Parser
*/

bool lambda_parse(struct lambda_lex_token* tokens);
bool lambda_parse_syntax(struct lambda_lex_token* tokens);

#endif LAMBDA_PARSE_HPP