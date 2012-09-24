#include <lambda_mem.h>
#include <stdio.h>

#if defined(_WIN32)
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#elif defined(__linux__) || defined(__APPLE__)
	#include <sys/mman.h>
#endif

void* lambda_alloc(long size, bool executable)
{
#if defined(_WIN32)
	return VirtualAlloc(0, size, MEM_COMMIT, executable ? PAGE_EXECUTE_READWRITE : PAGE_READWRITE);
#elif defined(__linux__) || defined(__APPLE__)
	void* p = mmap(0, size + sizeof(long), PROT_READ | PROT_WRITE | (executable ? PROT_EXEC : 0), MAP_PRIVATE | MAP_ANON, -1, 0);
	*(long*)p = size;
	return (long*)p + 1;
#endif
}

void lambda_free(void* address)
{
#if defined(_WIN32)
	VirtualFree(address, 0, MEM_RELEASE);
#elif defined(__linux__) || defined(__APPLE__)
	munmap((long*)address - 1, *((long*)address - 1));
#endif
}