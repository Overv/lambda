#ifndef LAMBDA_COMPILE_HPP
#define LAMBDA_COMPILE_HPP

#include <lambda_types.h>
#include <lambda_lex.h>

/*
	Compiler
*/

lambda_func lambda_compile_tokens(struct lambda_lex_token* tokens);

#endif