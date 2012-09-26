#include <stdio.h>
#include <lambda.h>

int main()
{
	int x, y;

	lambda_func f = lambda_compile("3+x+5");

	/*for (x = 1; x <= 10; x++) {
		y = f(x);
		printf("%d^2 = %d\n", x, y);
	}*/

	printf("%p\n", f);
	
	lambda_cleanup(f);
	
	return 0;
}