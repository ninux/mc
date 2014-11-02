/*
* menu.c - Menu program
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
#include <string.h>
#include "menu.h"
#include "debug.h"

/* define help strings */
#define MENU_HELP_HELP	"List avialable commands"
#define MENU_HELP_ADD	"Add a new address entry"
#define MENU_HELP_LIST	"List available address entries"
#define MENU_HELP_QUIT	"Exit the current session"

/* define some menu messages */
#define MENU_INVALID	"error: invalid syntax, see help"

#define MENU_CMD_HELP	"help"
#define MENU_CMD_ADD	"add"
#define MENU_CMD_LIST	"list"
#define MENU_CMD_QUIT	"quit"

/* define maximum length for inputs */
#define MAX_LINE 10

/* */
#define TYPE_CMD "> "

char *get_input(void);

int menu_help(void)
{
	_dbgmsg("executing help");
	printf("Commands:\n");
	printf("\t" MENU_CMD_HELP "\t" MENU_HELP_HELP "\n");
	printf("\t" MENU_CMD_ADD "\t"  MENU_HELP_ADD "\n");
	printf("\t" MENU_CMD_LIST "\t" MENU_HELP_LIST "\n");
	printf("\t" MENU_CMD_QUIT "\t" MENU_HELP_QUIT "\n");
	return 0;
}

int menu_add(void)
{
	_dbgmsg("executing add");
	return 0;
}

int menu_list(void)
{
	_dbgmsg("executing list");
	return 0;
}

void menu_quit(void)
{
	_dbgmsg("exiting program by user");
	exit(0);
}

int menu_check_command(void)
{
	int command;
	char *input;
	input = get_input();

	if (strcmp(input, MENU_CMD_HELP) == 0) {
		command = HELP;
	} else if (strcmp(input, MENU_CMD_ADD) == 0) {
		command = ADD;
	} else if (strcmp(input, MENU_CMD_LIST) == 0) {
		command = LIST;
	} else if (strcmp(input, MENU_CMD_QUIT) == 0) {
		command = QUIT;
	} else {
		command = -1;
	}
	_dbgmsg("evaluated command is %i", command);
	free(input);
	return command;
}

char *get_input(void)
{
	char raw[MAX_LINE];
	char *input;
	printf(TYPE_CMD);
	if (fgets(raw, MAX_LINE, stdin) == NULL) {
		_dbgerr("could not read input");
		printf(MENU_INVALID "\n");
		return NULL;
	} else {
		strtok(raw, "\n");
		_dbgmsg("read input \"%s\"", raw);
	}

	input = malloc(strlen(raw));
	if (input == NULL) {
		_dbgerr("allocating memory failed");
		return NULL;
	} else {
		_dbgmsg("allocated memory for \"%s\" at %i", raw, input);
		strcpy(input, raw);
	}

	return input;
}

int menu_execute(int command)
{
	switch (command) {
	case HELP:	menu_help(); break;
	case ADD:	menu_add(); break;
	case LIST:	menu_list(); break;
	case QUIT:	menu_quit(); break;
	default:	printf(MENU_INVALID "\n"); break;
	}
	return 0;
}
