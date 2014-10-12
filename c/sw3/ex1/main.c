/*
* main.c - Exercise 1, SW3
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
	entry_ptr_t ptr;

	full_name_t a;
	full_name_t b;
	full_name_t c;
	full_name_t *d;

	entry_t x;
	entry_t y;
	entry_t z;

	#ifdef DEBUG
		printf("DEBUG: started application\n");
	#endif

	a.first = "Nino";
	a.last = "Ninux";

	b.first = "Brian";
	b.last = "Kerninghan";

	c.first = "Dennis";
	c.last = "Ritchie";

	d = create_person("Someone", "Else");
	printf("Name: %s %s\n", d->first, d->last);

	x.name = a;
	x.next = &y;

	y.name = b;
	y.next = &z;

	z.name = c;
	z.next = NULL;

	ptr = &x;

	while ((*ptr).next != NULL) {
		printf("%s %s is linked to %s %s\n",
		       (*ptr).name.first,
		       (*ptr).name.last,
		       (*(*ptr).next).name.first,
		       (*(*ptr).next).name.last
		);
		ptr = ((*ptr).next);
	}

	#ifdef DEBUG
		printf("DEBUG: exiting application\n");
	#endif

	return 0;
}
