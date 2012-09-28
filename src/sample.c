#include <stdio.h>
#include <lambda.h>

int main()
{
	int i;

	lambda_func f = lambda_compile("3xx+5x-9");

	for (i = 1; i <= 10; i++) {
		printf("%d squared = %d\n", i, f(i));
	}

	lambda_cleanup(f);

	return 0;
}