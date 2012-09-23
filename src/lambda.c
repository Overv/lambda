#include <lambda.h>
#include <string.h>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#elif defined(__linux__)
#include <sys/mman.h>
#endif

lambda_func lambda_compile(const char* expr)
{
#if defined(_WIN32)
	char* foo = (char*)VirtualAlloc(0, 8, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
#elif defined(__linux__)
	char* foo = mmap(0, 8, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif

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
#if defined(_WIN32)
	VirtualFree(f, 8, MEM_RELEASE);
#elif defined(__linux))
	munmap(f, 4096);
#endif
}