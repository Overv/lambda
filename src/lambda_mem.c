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
	return VirtualAlloc(0, size, MEM_COMMIT, executable ? PAGE_EXECUTE_READWRITE : PAGE_READWRITE);
#elif defined(__linux__)
	return mmap(0, size, PROT_READ | PROT_WRITE | (executable ? PROT_EXEC : 0), MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif
}

void lambda_free(void* address)
{
#if defined(_WIN32)
	VirtualFree(address, 0, MEM_RELEASE);
#elif defined(__linux))
	munmap(address, size);
#endif
}