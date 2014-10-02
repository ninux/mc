/*
* ninux.c - Exercise 1.4
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

#define SELECT "Select menu item "
#define SELECTION "Changing to menu item --> "
#define QUIT "Goodbye!"

#define OPTION_0 'Q'	/* Quit the program */
#define OPTION_1 'A'
#define OPTION_2 'B'
#define OPTION_3 'C'

#define OPTION_ERROR "Sorry, invalid option"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int show_selection_a(void)
{
	printf("%s%c\n", SELECT, OPTION_1);
	return(0);
}

int show_selection_b(void)
{
	printf("%s%c\n", SELECT, OPTION_2);
	return(0);
}

int show_selection_c(void)
{
	printf("%s%c\n", SELECT, OPTION_3);
	return(0);
}

int show_options(void)
{
	printf("\t%c\n", OPTION_1);
	printf("\t%c\n", OPTION_2);
	printf("\t%c\n", OPTION_3);
	return(0);
}

char get_input()
{
	char input;
	while(!isalpha (input = getchar())){
		/* NO-OP */
	}
	input = toupper(input);
	return(input);
}

int show_selection(char option)
{
	switch (option){
	case OPTION_0:
		printf("%s\n", QUIT);
		break;
	case OPTION_1:
		printf("%s%c\n", SELECTION, OPTION_1);
		break;
	case OPTION_2:
		printf("%s%c\n", SELECTION, OPTION_2);
		break;
	case OPTION_3:
		printf("%s%c\n", SELECTION, OPTION_3);
		break;
	default:
		printf("%s\n", OPTION_ERROR);
		break;
	}
	return(0);
}
