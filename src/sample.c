#include <stdio.h>
//#include <lambda.h>
#include <lambda_asm.h>

int main()
{
	int x, y;

	lambda_func f = lambda_compile("x*x");

	for (x = 1; x <= 10; x++) {
		y = f(x);
		printf("%d^2 = %d\n", x, y);
	}
	
	lambda_cleanup(f);

	getchar();
	return 0;
}