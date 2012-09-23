#ifndef LAMBDA_HPP
#define LAMBDA_HPP

// Headers
#include <lambda_types.h>

// Main interface
lambda_func lambda_compile(const char* expr);
void lambda_cleanup(lambda_func f);

#endif