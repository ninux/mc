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
* with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "address.h"
#include "debug.h"
#include "record.h"

#define DATA_SEPARATOR	", "
#define DATA_END	";\n"

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

static int data_to_address(int n);

static int address_to_data(entry_ptr_t ent);

static int get_entry_length(entry_ptr_t ent);

static int get_digits(int a);

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

	/* THE PROGRAM CRASHES HERE AFTER "delete" AND THEN "add" */

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
	entry_ptr_t ent;

	ctr = 1;
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
	head = NULL;
}

static void delete_recursive(entry_ptr_t ent)
{
	if (ent != NULL) {
		if ((ent->next) != NULL) {
			delete_recursive(ent->next);
		}
		free(ent->data->city);
		free(ent->data->zipcode);
		free(ent->data->number);
		free(ent->data->street);
		free(ent->data->lastname);
		free(ent->data->firstname);
		free(ent->next);
		_dbgnice("freed an entry");
	} else {
		_dbgwarn("list is empty");
	}
}

void read_all(void)
{
	char *line;
	int ctr;

	ctr = 1;

	while ((line = read_address(ctr)) != NULL) {
		strtok(line, "\n");
		_dbgmsg("Entry %2i: %s\n", ctr, line);
		data_to_address(ctr);
		ctr++;
	}

	free(line);
}



static int data_to_address(int n)
{
	_dbgmsg("parsing data from file for entry %i", n);

	char *line;
	char c;
	int i;		/* data segment			*/
	int pos;	/* position in data segment	*/
	int ctr;	/* position in inputline	*/
	int ret;

	char *firstname;
	char *lastname;
	char *street;
	char *nr;
	int *number;
	char *zp;
	int *zipcode;
	char *city;

	i = 0;
	ctr = 0;
	pos = 0;

	line = read_address(n);
	if (line == NULL) {
		return -1;
	}
	_dbgmsg("read data entry as \"%s\"", line);

	/* prepare the memory for the data */
	firstname = malloc(strlen(line));
	lastname = malloc(strlen(line));
	street = malloc(strlen(line));
	number = malloc(sizeof(int));
	nr = malloc(strlen(line));
	zipcode = malloc(sizeof(int));
	zp = malloc(strlen(line));
	city = malloc(strlen(line));

	/* initialize the data */
	firstname[0] = '\0';
	lastname[0] = '\0';
	street[0] = '\0';
	nr[0] = '\0';
	zp[0] = '\0';
	city[0] = '\0';

	while (((c = line[ctr]) != ';')	&& (i <= 5)) {
		if (c == '#') {
			_dbgwarn("found comment -> skipping rest of line");
			return 0;
		} else if (c == '\n') {
			_dbgwarn("found newline -> skipping rest of line");
			return 0;
		} else if (c == ',') {
			i++;
			ctr++;
			pos = 0;
		} else {
			if (c == ' ') {
				ctr++;
			} else {
				switch (i) {
				case 0:	firstname[pos] = c;
					firstname[pos+1] = '\0';
					break;
				case 1: lastname[pos] = c;
					lastname[pos+1] = '\0';
					break;
				case 2: street[pos] = c;
					street[pos+1] = '\0';
					break;
				case 3: nr[pos] = c;
					nr[pos+1] = '\0';
					break;
				case 4: zp[pos] = c;
					zp[pos+1] = '\0';
					break;
				case 5: city[pos] = c;
					city[pos+1] = '\0';
					break;
				default:
					_dbgerr("something went wrong at parsing "
					"\"%c\"", c);
					break;
				}
				pos++;
				ctr++;
			}
		}
	}

	/* fitting memory and data */
	firstname = realloc(firstname, strlen(firstname));
	lastname = realloc(lastname, strlen(lastname));
	street = realloc(street, strlen(street));
	*number = atoi(nr);
	free(nr);
	*zipcode = atoi(zp);
	free(zp);
	city = realloc(city, strlen(city));

	_dbgmsg("finished parsing -> adding new address entry");
	ret = add_address(firstname, lastname, street, number, zipcode, city);

	free(firstname);
	free(lastname);
	free(street);
	free(number);
	free(zipcode);
	free(city);
	_dbgnice("freed all address data for entry %i", n);

	return ret;
}

void write_all(void)
{
	entry_ptr_t ent;
	ent = head;

	while (ent != NULL) {
		address_to_data(ent);
		ent = ent->next;
	}
}

static int address_to_data(entry_ptr_t ent)
{
	int length;
	int offset;

	int son = get_digits(*(ent->data->number))+1;
	int soz = get_digits(*(ent->data->zipcode))+1;

	char nr[son];
	char zip[soz];

	offset = 5*(strlen(DATA_SEPARATOR)) + strlen(DATA_END);
	length = get_entry_length(ent) + offset;

	char line[length];
	_dbgmsg("reserved %i characters for the line", length);

	strcpy(line, ent->data->firstname);
	strcat(line, DATA_SEPARATOR);
	strcat(line, ent->data->lastname);
	strcat(line, DATA_SEPARATOR);
	strcat(line, ent->data->street);
	strcat(line, DATA_SEPARATOR);
	sprintf(nr, "%i", *(ent->data->number));
	strcat(line, nr);
	strcat(line, DATA_SEPARATOR);
	sprintf(zip, "%i", *(ent->data->zipcode));
	strcat(line, zip);
	strcat(line, DATA_SEPARATOR);
	strcat(line, ent->data->city);
	strcat(line, DATA_END);

	_dbgmsg("created line \"%s\"", line);
	write_address(line);

	return 0;
}

static int get_entry_length(entry_ptr_t ent)
{
	int length;

	length = 0;

	length += strlen(ent->data->firstname);
	length += strlen(ent->data->lastname);
	length += strlen(ent->data->street);
	length += get_digits(*(ent->data->number));
	length += get_digits(*(ent->data->zipcode));
	length += strlen(ent->data->city);

	_dbgmsg("calculated %i characters for the entry", length);
	return length;
}

static int get_digits(int a)
{
	int nod;
	nod = (int)((log10(abs(a))) + 1);
	_dbgmsg("calculated %i digits for %i", nod, a);
	return nod;
}
