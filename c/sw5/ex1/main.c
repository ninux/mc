/*
* main.c - Matrix creation
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
#include "matrix.h"
#include "debug.h"

int main(int argv, char **argc)
{
	int **m;
	int rows, cols, init;

	_dbginfo();
	_dbgmsg("started main");

	if (argv == 4) {
		rows = atoi(argc[1]);
		cols = atoi(argc[2]);
		init = atoi(argc[3]);

		_dbgmsg("%i parameters given:", argv);
		_dbgmsg("\trows\t%i", rows);
		_dbgmsg("\tcolumns\t%i", cols);
		_dbgmsg("\tinitial\t%i", init);

	} else if (argv == 1) {
		_dbgwarn("no parameters given "
			"-> creating default matrix 3x3 "
			"initialized with 3");
		rows = 3;
		cols = 3;
		init = 3;
	} else {
		_dbgerr("wrong syntax -> exiting...");
		printf("wrong syntax\n");
		printf("exiting...\n");
		return -1;
	}

	m = create_matrix(rows, cols, init);
	destroy_matrix(m);

	_dbgmsg("exiting main");
	return 0;
}
