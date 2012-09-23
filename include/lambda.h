#ifndef LAMBDA_HPP
#define LAMBDA_HPP

// Headers
#include <stdlib.h>

// Compiled lambda expression
typedef int (*lambda_func)(int);

// Application interface
lambda_func lambda_compile(const char* expr);
void lambda_cleanup(lambda_func f);

#endif