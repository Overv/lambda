#include <lambda_mem.h>
#include <stdio.h>

#if defined(_WIN32)
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#elif defined(__linux__)
	#include <sys/mman.h>
#endif

void* lambda_alloc(long size, bool executable)
{
#if defined(_WIN32)
	long* p = (long*)VirtualAlloc(0, size + sizeof(long), MEM_COMMIT, executable ? PAGE_EXECUTE_READWRITE : PAGE_READWRITE);
#elif defined(__linux__)
	long* p = (long*)mmap(0, size + sizeof(long), PROT_READ | PROT_WRITE | (executable ? PROT_EXEC : 0), MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif

	p[0] = size;

	return p + 1;
}

void lambda_free(void* address)
{
	long size = *((long*)address - 1);

#if defined(_WIN32)
	VirtualFree(address, size + sizeof(long), MEM_RELEASE);
#elif defined(__linux))
	munmap(address, size + sizeof(long));
#endif
}