/*
* list.c - Exercise 1, SW2
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
#include <stdio.h>
#include <ctype.h>
#include "list.h"
#include "ninux.h"

#define HELP 'H'
#define LIST 'L'
#define NEW  'N'
#define QUIT 'Q'

extern entry_ptr_t head;

char get_input()
{
	char input;
	while(!isalpha (input = getchar())){
		/* NO-OP */
	}
	input = toupper(input);
	return(input);
}

int check_command(char cmd)
{
	switch (cmd) {
	case LIST:
		plist(head);
		break;
	case NEW:
		add();
		break;
	case QUIT:
		quit();
		break;
	case HELP:
		help(cmd);
		break;
	default:
		help(cmd);
		break;
	}
	return 0;
}

int help(char cmd)
{
	#ifdef DEBUG
	#endif
	if (cmd != HELP) {
		printf("invalid option \"%c\"\n", cmd);
		printf("\nusage:");
	} else {
		printf("help\n\nusage:");
	}
	printf("\t%c\tprint list\n",LIST);
	printf("\t%c\tnew entry\n", NEW);
	printf("\t%c\tquit\n", QUIT);

	return 0;
}

int quit(void)
{
	printf("exiting...\n");
	return 0;
}
