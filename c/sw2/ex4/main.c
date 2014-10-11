/*
* FILENAME.c - Exercise 4, SW2
*
* Copyright (C) 2014 Ervin Mazlagic <nino.ninux@gmail.com>
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or (at
* your option) any later version.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* walong with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include <stdio.h>
#include <stdlib.h>
#include <ninux.h>

int main(int argc, char **argv)
{
	int input;
	char *name;

	#ifdef DEBUG
		printf("DEBUG: %i arguments given\n", argc);
	#endif

	if (argc < 2) {
		printf("no value given\n");
		printf("exiting...\n");
		return -1;
	} else if (argc > 2) {
		printf("to many arguments\n");
		printf("exiting...\n");
		return -1;
	} else {
		input = atoi(argv[1]);
		#ifdef DEBUG
			printf("DEBUG: input value = %i\n", input);
		#endif
	}

	name = color_name(input);
	printf("The vale \"%i\" is associated with \"%s\"\n", input, name);

	return 0;
}
