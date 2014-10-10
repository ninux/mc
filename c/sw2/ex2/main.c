/*
* main.c - Exercise 2
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

int main(int argc, char **argv)
{
	int my_number;
	char *tmp;

	#ifdef DEBUG
		printf("DEBUG: ON\n");
	#endif

	if (argc < 1) {
		printf("no number given\n");
		printf("exiting...\n");
		return -1;
	} else if (argc > 2) {
		printf("to many arguments given\n");
		printf("exiting...\n");
		return -1;
	} else {
		my_number = atoi(argv[1]);
	}

	#ifdef DEBUG
		printf("DEBUG: given parameter = %i", my_number);
	#endif

	tmp = itoa(my_number);
	printf("Your number is %s\n", tmp);
	free(tmp);

	return(0);
}
