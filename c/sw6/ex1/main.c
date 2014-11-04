/*
* main.c - Main program for address management
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
#include "debug.h"
#include "menu.h"
#include "info.h"
#include "address.h"

int main(int argc, char **argv)
{
	_dbginfo();
	_dbgmsg("starting program");

	int command;
	command = 0;
	printf("\n" ABOUT "\n\n");
	printf("Wlecome to the ninux address management program!\n");
	while (command != QUIT) {
		command = menu_check_command();
		menu_execute(command);
	}

	_dbgmsg("exiting program automatically");
	return 0;
}
