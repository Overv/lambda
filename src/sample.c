#include <stdio.h>
#include <lambda.h>

int main()
{
	int x, y;

	lambda_func f = lambda_compile("x");

	for (x = 1; x <= 10; x++) {
		y = f(x);
		printf("%d^2 = %d\n", x, y);
	}

	lambda_cleanup(f);
	
	return 0;
}