/*
* ninux.c - Exercise 2
*
* Copyright (C) 2014 Ervin Mazlagic <nino.ninux@gmail.com>
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or (at
* your option) any later version.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ninux.h>

char *itoa(int input)
{
	char *digits;		/* for the ascii representation*/
	int size;		/* number of digits */
	int ctr;		/* arbitrary counter */

	size = get_decimal_size(input);
	digits = (char*) malloc(size*sizeof(char) + '\0');
	ctr = size-1;
	while(ctr >= 0) {
		digits[ctr] = (input % 10) + 0x30;
		input = (input/10);

		#ifdef DEBUG
			printf("DEBUG: next digit is = %c \trest = %i\n",
			       digits[ctr], input);
		#endif

		ctr--;
	}
	digits[size] = '\0';	/* set the string terminator */

	return digits;
}

int get_decimal_size(int input)
{
	int result;
	result = (int)log10(abs(input)) + 1;
	#ifdef DEBUG
		printf("DEBUG: evaluated %i digits for %i\n", result, input);
	#endif
	return result;
}
