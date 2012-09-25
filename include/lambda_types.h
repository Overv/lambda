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

#if defined(__GNUC__)
typedef int (__attribute__((fastcall)) *lambda_func)(int);
#else
typedef int (__fastcall *lambda_func)(int);
#endif

#endif
