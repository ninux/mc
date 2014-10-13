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
#include "ninux.h"

entry_ptr_t head;

int main(int argc, char **argv)
{
	char cmd;

	name_t  *a, *b, *c, *d, *e, *f;
	entry_t *z, *y, *x, *w, *v, *u;

	a = create_name("Nino", "Ninux");
	b = create_name("Dennis", "Ritchie");
	c = create_name("Brian", "Kerninghan");
	d = create_name("Linus", "Torvalds");
	e = create_name("Richard", "Stallman");
	f = create_name("Konrad", "Zuse");

	u = create_entry(*a, NULL);
	v = create_entry(*b, &u);
	w = create_entry(*c, &v);
	x = create_entry(*d, &w);
	y = create_entry(*e, &x);
	z = create_entry(*f, &y);

	head = z;

	/*
	plist(head);
	*/

	#ifdef DEBUG
		printf("DEBUG: started application\n");
	#endif

	do {
		printf("> ");
		cmd = get_input();
		check_command(cmd);
	} while (cmd != 'Q');

	#ifdef DEBUG
		printf("DEBUG: exiting application\n");
	#endif

	return 0;
}
