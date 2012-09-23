#ifndef LAMBDA_MEM_HPP
#define LAMBDA_MEM_HPP

#include <lambda_types.h>

/*
	Memory management
*/

void* lambda_alloc(long size, bool executable);
void lambda_free(void* address);

#endif