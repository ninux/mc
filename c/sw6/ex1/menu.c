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
* with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "debug.h"
#include "address.h"

/* define help strings */
#define MENU_HELP_HELP		"List avialable commands"
#define MENU_HELP_ADD		"Add a new address entry"
#define MENU_HELP_LIST		"List available address entries"
#define MENU_HELP_QUIT		"Exit the current session"
#define MENU_HELP_CLEAR		"Clear the screen"
#define MENU_HELP_DELETE	"Delete all address entries"
#define MENU_HELP_ABOUT		"Show the project info"
#define MENU_HELP_READ		"Read address from file"

/* define some menu messages */
#define MENU_INVALID	"error: invalid syntax, see help"

#define MENU_CMD_HELP	"help"
#define MENU_CMD_ADD	"add"
#define MENU_CMD_LIST	"list"
#define MENU_CMD_QUIT	"quit"
#define MENU_CMD_CLEAR	"clear"
#define MENU_CMD_DELETE	"delete"
#define MENU_CMD_ABOUT	"about"
#define MENU_CMD_READ	"read"

/* define maximum length for inputs */
#define MAX_LINE 20

/* */
#define TYPE_CMD "> "

char *get_input(void);
char *get_line(void);
void menu_delete(void);

int menu_help(void)
{
	_dbgmsg("executing help");
	printf("Commands:\n");
	printf("\t" STYLE_BOLD MENU_CMD_HELP STYLE_NO_BOLD
	       "\t" MENU_HELP_HELP "\n");
	printf("\t" STYLE_BOLD MENU_CMD_ADD STYLE_NO_BOLD
	       "\t" MENU_HELP_ADD "\n");
	printf("\t" STYLE_BOLD MENU_CMD_LIST STYLE_NO_BOLD
	       "\t" MENU_HELP_LIST "\n");
	printf("\t" STYLE_BOLD MENU_CMD_QUIT STYLE_NO_BOLD
	       "\t" MENU_HELP_QUIT "\n");
	printf("\t" STYLE_BOLD MENU_CMD_CLEAR STYLE_NO_BOLD
	       "\t" MENU_HELP_CLEAR "\n");
	printf("\t" STYLE_BOLD MENU_CMD_DELETE STYLE_NO_BOLD
	       "\t" MENU_HELP_DELETE "\n");
	printf("\t" STYLE_BOLD MENU_CMD_ABOUT STYLE_NO_BOLD
	       "\t" MENU_HELP_ABOUT "\n");
	printf("\t" STYLE_BOLD MENU_CMD_READ STYLE_NO_BOLD
	       "\t" MENU_HELP_READ "\n");
	return 0;
}

int menu_add(void)
{
	_dbgmsg("executing add");

	char *firstname;
	char *lastname;
	char *street;
	int *number;
	int *zipcode;
	char *city;

	printf("\tFirst name:\t");
	firstname = get_line();

	printf("\tLast Name:\t");
	lastname = get_line();

	printf("\tStreet:\t\t");
	street = get_line();

	printf("\tNumber:\t\t");
	number = malloc(sizeof(int));
	*number = atoi(get_line());

	printf("\tZipcode:\t");
	zipcode = malloc(sizeof(int));
	*zipcode = atoi(get_line());

	printf("\tCity:\t\t");
	city = get_line();

	#ifdef DEBUG
		_dbgmsg("First name:\t%s", firstname);
		_dbgmsg("Last name:\t%s", lastname);
		_dbgmsg("Street:\t%s", street);
		_dbgmsg("Number:\t%i", *number);
		_dbgmsg("Zipcode:\t%i", *zipcode);
		_dbgmsg("City:\t\t%s", city);
	#endif

	add_address(firstname, lastname, street, number, zipcode, city);

	free(firstname);
	free(lastname);
	free(street);
	free(number);
	free(zipcode);
	free(city);
	_dbgnice("freeing inputs");

	return 0;
}

int menu_list(void)
{
	_dbgmsg("executing list");
	show_all();
	return 0;
}

void menu_quit(void)
{
	_dbgmsg("exiting program by user");
	/* delete_all(); */
	menu_delete();
	exit(0);
}

void menu_clear(void)
{
	system("clear");
}

void menu_delete(void)
{
	delete_all();
}

void menu_about(void)
{
	char c;
	FILE *file;
	file = fopen("about.txt", "r");
	if (file) {
		while ((c = getc(file)) != EOF) {
			putchar(c);
		}
		fclose(file);
	}
}

void menu_read(void)
{
	_dbgmsg("reading address from file");
	read_all();
}

char *get_line(void)
{
	char *input;
	char raw[MAX_LINE];
	fgets(raw, MAX_LINE, stdin);
	strtok(raw, "\n");
	input = malloc(strlen(raw));
	strcpy(input, raw);
	return input;
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
	} else if (strcmp(input, MENU_CMD_CLEAR) == 0) {
		command = CLEAR;
	} else if (strcmp(input, MENU_CMD_DELETE) == 0) {
		command = DELETE;
	} else if (strcmp(input, MENU_CMD_ABOUT) == 0) {
		command = ABOUT;
	} else if (strcmp(input, MENU_CMD_READ) == 0) {
		command = READ;
	} else {
		command = -1;
	}
	_dbgmsg("evaluated command is %i", command);
	free(input);
	_dbgnice("freeing input");
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
	case CLEAR:	menu_clear(); break;
	case DELETE:	menu_delete(); break;
	case ABOUT:	menu_about(); break;
	case READ:	menu_read(); break;
	default:	_dbgerr("wrong syntax");
			printf(MENU_INVALID "\n"); break;
	}
	return 0;
}
