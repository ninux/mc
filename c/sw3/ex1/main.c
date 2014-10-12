/*
* FILENAME.c - DESCRIPTION
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
#include <string.h>
#include "list.h"

int main(int argc, char **argv)
{
	full_name_t a;
	entry_t b;

	#ifdef DEBUG
		printf("DEBUG: started application\n");
	#endif

	a.first = "Nino";
	a.last = "Ninux";

	printf("Your name is: %s %s\n", a.first, a.last);

	b.name = a;
	b.next = NULL;

	printf("Your name is: %s %s\n", b.name.first, b.name.last);

	#ifdef DEBUG
		printf("DEBUG: exiting application\n");
	#endif

	return 0;
}
