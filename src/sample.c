#include <stdio.h>
#include <lambda.h>

int main()
{
	int i;

	lambda_func f = lambda_compile("104/13");

	for (i = 1; i <= 10; i++) {
		printf("%d^2 = %d\n", i, f(i));
	}
	
	lambda_cleanup(f);

	getchar();
	return 0;
}