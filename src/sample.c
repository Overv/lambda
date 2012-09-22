#include <stdio.h>
#include <lambda.h>

int f() {
	return 1337;
}

int main()
{
	lambda_func f = lambda_compile("x*x");

	for (int i = 1; i <= 10; i++) {
		printf("%d^2 = %d\n", i, f(i));
	}

	lambda_cleanup(f);

	return 0;
}