#include <stdio.h>
#include <stdlib.h>

int read_line(char s[], int limit)
{
	int i;
	char c;

	i = 0;

	c = getchar();
	while ((c != EOF) && (c != '\n') && (i < (limit - 1))){
		s[i] = c;
		i++;
		c = getchar();
	}

	if (c == '\n') {
		s[i] = '\n';
		i++;
	}

	s[i] = '\0';

	return(i);
}

