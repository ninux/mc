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
#include <stdlib.h>
#include <string.h>
#include "list.h"

full_name_t *create_person(char *first_name, char *last_name)
{
	full_name_t *person;
	person = malloc(strlen(first_name) + strlen(last_name));
	person->first = first_name;
	person->last = last_name;

	return person;
}

entry_t *pack(full_name_t *person)
{
	entry_t *new;
	new = malloc(sizeof *person);
	new->name = *person;
	new->next = NULL;

	return new;
}

entry_t *create_entry(char *first_name, char *last_name)
{
	entry_t *element;
	full_name_t *person;
	person = malloc(strlen(first_name) + strlen(last_name));
	person->first = first_name;
	person->last = last_name;
	element = pack(person);

	return element;
}

entry_t *add(entry_t *root, entry_t *born)
{
	entry_ptr_t ptr;
	ptr = root;

	while ((*ptr).next != NULL) {
		ptr = ((*ptr).next);
	}

	(*ptr).next = born;

	return born;
}

entry_t *cadd(entry_t *root, char *first_name, char *last_name)
{
	entry_t *element;
	full_name_t *person;
	entry_ptr_t ptr;

	ptr = root;

	person = malloc(strlen(first_name) + strlen(last_name));
	person->first = first_name;
	person->last = last_name;

	element = malloc(sizeof *person);
	element->name = *person;
	element->next = NULL;

	while ((ptr->next) != NULL) {
		ptr = (ptr->next);
	}

	ptr->next = element;

	return element;
}
