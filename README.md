# lambda

This is an experimental library for compiling anonymous functions based on C#'s lambda expressions at runtime. It serves as a minimal example of runtime code generation and not necessarily something useful in practice. The library only supports the x86 instruction set as of this time.

## Sample

```c
#include <stdio.h>
#include <lambda.h>

int main()
{
	int x;

	lambda_func f = lambda_compile("3xx+5x-9");

	for (x = 1; x <= 10; x++) {
		printf("%d squared = %d\n", x, f(x));
	}

	lambda_cleanup(f);

	return 0;
}
```

## Todo

* Floating point numbers
* Bracket support

## License

MIT