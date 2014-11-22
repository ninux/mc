#include <stdio.h>

int main(int argv, char **argc)
{
	int a, b, c;

	c = 0;
	a = 5;
	b = 2;

	c += a;
	c += b;

	printf("%c", c);

	return 0;
}
