#include <lambda.h>
#include <string.h>
#include <sys/mman.h>

lambda_func lambda_compile(const char* expr)
{
	char* foo = mmap(0, 8, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	foo[0] = 0xB8;
	foo[1] = 0x00;
	foo[2] = 0x00;
	foo[3] = 0x00;
	foo[4] = 0x00;
	foo[5] = 0xC3;

	return (lambda_func)foo;
}

void lambda_cleanup(lambda_func f)
{
	munmap(f, 4096);
}