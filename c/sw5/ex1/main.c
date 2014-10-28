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
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include "matrix.h"
#include "debug.h"

int main(int argv, char **argc)
{
	#ifdef DEBUG
		/* limiting memory space */
		struct rlimit rl;
		getrlimit(RLIMIT_AS, &rl);
		_dbgmsg("default memory limit is %lld", (long long
							 int)rl.rlim_cur);
		rl.rlim_cur = MEMORY_LIMIT;
		setrlimit(RLIMIT_AS, &rl);
		getrlimit(RLIMIT_AS, &rl);
		_dbgwarn("change memory space to %lld", (long long
							int)rl.rlim_cur);
	#endif

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
