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
#include <unistd.h>
#include "debug.h"

#define ADDRESS_FILE	"database.txt"
#define LINE_LIMIT	80

extern char *datain;
extern char *dataout;

int file_existence(const char *filename)
{
	return (access(filename, F_OK) != -1);
}

char *read_address(int n)
{
	int target;
	int position;
	char line[LINE_LIMIT];
	char *address;
	FILE *file;

	target = n;
	position = 1;
	file = fopen(datain, "r");

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
	} else {
		if (file_existence(datain)) {
			_dbgerr("something went wrong opening \"%s\"", datain);
			printf("something went wrong opening \"%s\"\n", datain);
		} else {
			_dbgwarn("no such file \"%s\"", datain);
			printf("no such file \"%s\"\n", datain);
		}
		return NULL;
	}
}

int write_address(char *line)
{
	FILE *file;

	file = fopen(dataout, "a");

	if (file) {
		fprintf(file, line);
	} else {
		if (file_existence(datain)) {
			_dbgerr("something went wrong opening \"%s\"", dataout);
			printf("something went wrong opening \"%s\"\n",
			       dataout);
		} else {
			_dbgwarn("no such file \"%s\"", dataout);
			printf("no such file \"%s\"\n", dataout);
		}
	}

	fclose(file);
}
