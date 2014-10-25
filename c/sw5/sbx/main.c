#include <stdio.h>

int add(int a, int b)
{
	return (a + b);
}

int main(int argv, char **argc)
{
	int a, b;

	if (argv == 3) {
		a = atoi(argc[1]);
		b = atoi(argc[2]);
	} else {
		a = 2;
		b = 3;
	}

	int (*foo)(int, int);
	foo = &add;

	printf("Usual function:\t\t%i + %i = %i\n", a, b, add(a, b));
	printf("Callback function:\t%i + %i = %i\n", a, b, foo(a, b));

	return 0;
}
