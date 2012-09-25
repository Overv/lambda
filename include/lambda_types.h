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

// Both GCC and MSC use the fastcall convention on 32-bit to ensure that x lands in the ECX
// register instead of the stack. On 64-bit platforms with GCC, we have to assume the compiler
// uses the EDI register instead, because fastcall is not supported.
#if defined(_MSC_VER)
#define LAMBDA_FASTCALL
typedef int (__fastcall *lambda_func)(int);
#elif defined(__GNUC__) && !defined(__LP64__)
#define LAMBDA_FASTCALL
typedef int (__attribute__((fastcall)) *lambda_func)(int);
#else
typedef int (*lambda_func)(int);
#endif

#endif
