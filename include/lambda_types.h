#ifndef LAMBDA_TYPES_HPP
#define LAMBDA_TYPES_HPP

/*
	Types
*/

typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char uchar;

typedef int bool;
#define false 0
#define true 1

#ifndef NULL
#define NULL 0
#endif

// Both GCC and MSVC use the fastcall convention on 32-bit to ensure that the parameter
// is passed via the ECX register. On 64-bit platforms we assume the System V AMD64 ABI
// on GCC and Microsoft's calling convention on MSVC.
#if defined(_MSC_VER)
	#define REG_PARAM ECX
	typedef int (__fastcall *lambda_func)(int);
#elif defined(__GNUC__)
	#if defined(__LP64__)
		#define REG_PARAM EDI
		typedef int (*lambda_func)(int);
	#else
		#define REG_PARAM ECX
		typedef int (__attribute__((fastcall)) *lambda_func)(int);
	#endif
#endif

#endif