/*
* address.c - Address
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
#include "address.h"
#include "debug.h"

typedef struct {
	char *firstname;
	char *lastname;
	char *street;
	int *number;
	int *zipcode;
	char *city;
} address_t;

typedef struct entry *entry_ptr_t;

typedef struct entry {
	address_t *data;
	entry_ptr_t next;
} entry_t;

static entry_ptr_t head = NULL;

static address_t *create_address(char *firstname,
				 char *lastname,
				 char *street,
				 int *number,
				 int *zipcode,
				 char *city);

static entry_ptr_t create_entry(address_t *data,
				entry_ptr_t prev,
				entry_ptr_t next);

static int add_entry(address_t *data);

static void delete_recursive(entry_ptr_t ent);

static void deleta_all(void);

int add_address(char *firstname,
		char *lastname,
		char *street,
		int *number,
		int *zipcode,
		char *city);

void show_all(void);

int add_address(char *firstname,
		char *lastname,
		char *street,
		int *number,
		int *zipcode,
		char *city)
{
	address_t *addr;
	addr = create_address(firstname,
			      lastname,
			      street,
			      number,
			      zipcode,
			      city);
	add_entry(addr);
	return 0;
}

static int add_entry(address_t *data)
{
	entry_ptr_t ent;
	ent = malloc(sizeof(entry_t));
	if (ent == NULL) {
		_dbgerr(MEMORY_ALLOCATION_FAIL);
		return -1;
	} else {
		_dbgmsg("allocated memory for a new entry");
		ent->data = data;
		ent->next = head;
		head = ent;
		_dbgmsg("new head at %i", head);
	}
	return 0;
}

static address_t *create_address(char *firstname,
				 char *lastname,
				 char *street,
				 int *number,
				 int *zipcode,
				 char *city)
{
	address_t *n_address;
	n_address = malloc(sizeof(address_t));

	/* preparing address */
	if (n_address == NULL) {
		_dbgerr(MEMORY_ALLOCATION_FAIL);
		return NULL;
	} else {
		_dbgmsg("allocated memory for a new address");
	}

	/* preparing firstname to address */
	n_address->firstname = malloc(strlen(firstname));
	if (n_address->firstname == NULL) {
		_dbgerr(MEMORY_ALLOCATION_FAIL);
		free(n_address);
		n_address = NULL;
		return NULL;
	} else {
		_dbgmsg("allocated memory for a firstname \"%s\"", firstname);
		strcpy(n_address->firstname, firstname);
	}

	/* preparing lastname to address */
	n_address->lastname = malloc(strlen(lastname));
	if (n_address->lastname == NULL) {
		_dbgerr(MEMORY_ALLOCATION_FAIL);
		free(n_address->firstname);
		free(n_address);
		return NULL;
	} else {
		_dbgmsg("allocated memory for a lastname \"%s\"", lastname);
		strcpy(n_address->lastname, lastname);
	}

	/* preparing street to address */
	n_address->street = malloc(strlen(street));
	if (n_address->street == NULL) {
		_dbgerr(MEMORY_ALLOCATION_FAIL);
		free(n_address->lastname);
		free(n_address->firstname);
		free(n_address);
		return NULL;
	} else {
		_dbgmsg("allocated memory for a street \"%s\"", street);
		strcpy(n_address->street, street);
	}

	/* preparing number to address */
	n_address->number = malloc(sizeof(int));
	if (n_address->number == NULL) {
		_dbgerr(MEMORY_ALLOCATION_FAIL);
		free(n_address->street);
		free(n_address->lastname);
		free(n_address->firstname);
		free(n_address);
		return NULL;
	} else {
		_dbgmsg("allocated memory for a number \"%i\"", *number);
		*(n_address->number) = *number;
	}

	/* preparing zipcode to address */
	n_address->zipcode = malloc(sizeof(int));
	if (n_address->zipcode == NULL) {
		_dbgerr(MEMORY_ALLOCATION_FAIL);
		free(n_address->number);
		free(n_address->street);
		free(n_address->lastname);
		free(n_address->firstname);
		free(n_address);
		return NULL;
	} else {
		_dbgmsg("allocated memory for a zipcode \"%i\"", *zipcode);
		*(n_address->zipcode) = *zipcode;
	}

	/* preparing city to address */
	n_address->city = malloc(strlen(city));
	if (n_address->city == NULL) {
		_dbgerr(MEMORY_ALLOCATION_FAIL);
		free(n_address->zipcode);
		free(n_address->number);
		free(n_address->street);
		free(n_address->lastname);
		free(n_address->firstname);
		free(n_address);
		return NULL;
	} else {
		_dbgmsg("allocated memory for a city \"%s\"", city);
		strcpy(n_address->city, city);
		return n_address;
	}

}

void show_all(void)
{
	int ctr;
	ctr = 1;

	entry_ptr_t ent;
	ent = head;

	while (ent != NULL) {
		printf("Entry %2i:", ctr);
		printf("\t%s %s\n",
		       ent->data->firstname,
		       ent->data->lastname);
		printf("\t\t%s %i\n",
		       ent->data->street,
		       *(ent->data->number));
		printf("\t\t%i %s\n\n",
		       *(ent->data->zipcode),
		       ent->data->city);
		ent = ent->next;
		ctr++;
	}
}

void delete_all(void)
{
	delete_recursive(head);
}

static void delete_recursive(entry_ptr_t ent)
{

}
