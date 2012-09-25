#ifndef LAMBDA_MEM_HPP
#define LAMBDA_MEM_HPP

/*
	Executable memory management
*/

void* lambda_alloc(long size);
void lambda_free(void* address);

#endif