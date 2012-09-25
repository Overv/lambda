# lambda

This is an experimental library for compiling anonymous functions based on C#'s lambda expressions at runtime. It serves as a minimal example of runtime code generation and not necessarily something useful in practice. The library only supports the x86 instruction set as of this time.

## Sample

```c
#include <stdio.h>
#include <lambda.h>

int main()
{
	int i;

	lambda_func f = lambda_compile("x*x");

	for (i = 1; i <= 10; i++) {
		printf("%d squared = %d\n", i, f(i));
	}

	lambda_cleanup(f);

	return 0;
}
```

## Todo

* Parser
* Compiler

## License

MIT