/*
* list.c - Exercise 1, SW2
*
* Copyright (C) 2014 Ervin Mazlagic <nino.ninux@gmail.com>
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as ndet [-Wuninitialized]
[ninux@t430 ex1]$ make clean all
published by
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

#define MAX_NAMESIZE 20

extern entry_ptr_t head;

int plist(entry_ptr_t origin)
{
	entry_ptr_t ptr;

	#ifdef DEBUG
		printf("DEBUG: printing the list\n");
	#endif

	if (origin == NULL) {
		printf("list is empty\n");
		return -1;
	} else {
		ptr = origin;
	}

	printf("list\n");
	printf("\thead:\t[ %s %s\n",
	       (ptr->name)->first,
	       (ptr->name)->last);
	ptr = *(ptr->next);
	do {
		printf("\t\t-> %s %s\n",
		       (ptr->name)->first,
		       (ptr->name)->last);
		ptr = *(ptr->next);
	} while ((ptr->next) != NULL);
	printf("\ttail:\t-> %s %s ]\n",
		(ptr->name)->first,
		(ptr->name)->last);

	#ifdef DEBUG
		printf("DEBUG: end of list\n");
	#endif
	return 0;
}

int add(void)
{
	name_t *a_name;
	entry_t *a_entry;

	a_name = malloc(sizeof(name_t));
	a_entry = malloc(sizeof(entry_t));

	a_name = ask_name();
	a_entry = create_entry(a_name, head->next);

	head = a_entry;

	#ifdef DEBUG
		printf("DEBUG: adding entry to list\n");
		printf("DEBUG: new head at \"%s\" \"%s\"\n",
		       (head->name)->first,
		       (head->name)->last);
	#endif

	return 0;
}

name_t *create_name(char *first_name, char *last_name)
{
	name_t* p_name;

	p_name = (name_t*)malloc(sizeof(name_t));

	p_name->first = malloc(strlen(first_name));
	p_name->last = malloc(strlen(last_name));

	strcpy(p_name->first, first_name);
	strcpy(p_name->last, last_name);

	return p_name;
}


entry_t *create_entry(name_t *name, entry_ptr_t *next)
{
	entry_t *entry;

	entry = malloc(sizeof(name) + sizeof(entry_ptr_t));

	entry->name = name;
	entry->next = next;

	return entry;
}

name_t *ask_name(void)
{
	name_t *name;
	char first_name[MAX_NAMESIZE];
	char last_name[MAX_NAMESIZE];

	scanf("%*[^\n]"); (void) getchar ();
	printf("\tfirst name: ");
	fgets(first_name, MAX_NAMESIZE, stdin);
	strtok(first_name, "\n");

	printf("\tlast name: ");
	fgets(last_name, MAX_NAMESIZE, stdin);
	strtok(last_name, "\n");

	#ifdef DEBUG
		printf("DEBUG: given name is \"%s\" \"%s\"\n",
		       first_name, last_name);
	#endif

	name = create_name(first_name, last_name);
	return name;
}
