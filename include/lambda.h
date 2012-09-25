#ifndef LAMBDA_HPP
#define LAMBDA_HPP

#include <lambda_types.h>

lambda_func lambda_compile(const char* expr);
void lambda_cleanup(lambda_func f);

#endif