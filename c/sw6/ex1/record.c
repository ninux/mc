/*
* record.c - Recording and reading data from file
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
#include "debug.h"

#define ADDRESS_FILE	"database.txt"
#define LINE_LIMIT	80

char *read_address(int n)
{
	int target;
	int position;
	char line[LINE_LIMIT];
	char *address;
	FILE *file;

	target = n;
	position = 1;
	file = fopen(ADDRESS_FILE, "r");

	if (file) {
		while (fgets(line, LINE_LIMIT, file) != NULL) {
			_dbgmsg("read line \"%s\"", strtok(line, "\n"));
			if (position == target) {
				_dbgmsg("found the entry");
				address = malloc(strlen(line));
				if (address == NULL) {
					_dbgerr(MEMORY_ALLOCATION_FAIL);
				} else {
					_dbgmsg("allocated memory for address "
						"read from file");
					strcpy(address, line);
					fclose(file);
					return address;
				}
			} else {
				_dbgmsg("skipping this entry");
				position++;
			}
		}
	        fclose(file);
		_dbgerr("there's no entry %i", target);
		return NULL;
	}
}

int write_address(char *line)
{
	FILE *file;

	file = fopen(ADDRESS_FILE, "a");
	if (file == NULL) {
		_dbgerr("opening file " ADDRESS_FILE " failed");
	} else {
		fprintf(file, line);
	}


	fclose(file);
}
