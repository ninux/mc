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
#include <limits.h>
#include <math.h>
#include "menu.h"
#include "debug.h"
#include "address.h"

/* define maximum length for inputs */
#define MAX_LINE 40

/* */
#define TYPE_CMD "> "

/* define help strings */
#define MENU_HELP_HELP		"List avialable commands"
#define MENU_HELP_ADD		"Add a new address entry"
#define MENU_HELP_LIST		"List available address entries"
#define MENU_HELP_QUIT		"Exit the current session"
#define MENU_HELP_CLEAR		"Clear the screen"
#define MENU_HELP_DELETE	"Delete all address entries"
#define MENU_HELP_ABOUT		"Show the project info"
#define MENU_HELP_READ		"Read address-list from file"
#define MENU_HELP_FORMAT	"Show the address-field formats"
#define MENU_HELP_WRITE		"Append current address-list to file"

#define MENU_FORMAT		STYLE_BOLD \
				"\t[n] Field\tFormat\tSize\n" \
				"\t----------------------------\n" \
				STYLE_NO_BOLD \
				"\t[1] First name\tString\t%4i\n" \
				"\t[2] Last name\tString\t%4i\n" \
				"\t[3] Street\tString\t%4i\n" \
				"\t[4] Number\tInteger\t%4i\n" \
				"\t[5] Zipcode\tInteger\t%4i\n" \
				"\t[6] City\tString\t%4i\n", \
				MAX_LINE, \
				MAX_LINE, \
				MAX_LINE, \
				(int)((log10(abs(INT_MAX))) + 1), \
				(int)((log10(abs(INT_MAX))) + 1), \
				MAX_LINE

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
#define MENU_CMD_FORMAT	"format"
#define MENU_CMD_WRITE	"write"

extern char *datain;
extern char *dataout;

char *get_input(void);
char *get_line(void);
void menu_delete(void);

int menu_help(void)
{
	_dbgmsg("executing help");
	printf("Commands:\n");
	printf("\t" STYLE_BOLD MENU_CMD_ABOUT STYLE_NO_BOLD
	       "\t" MENU_HELP_ABOUT "\n");
	printf("\t" STYLE_BOLD MENU_CMD_ADD STYLE_NO_BOLD
	       "\t" MENU_HELP_ADD "\n");
	printf("\t" STYLE_BOLD MENU_CMD_CLEAR STYLE_NO_BOLD
	       "\t" MENU_HELP_CLEAR "\n");
	printf("\t" STYLE_BOLD MENU_CMD_DELETE STYLE_NO_BOLD
	       "\t" MENU_HELP_DELETE "\n");
	printf("\t" STYLE_BOLD MENU_CMD_FORMAT STYLE_NO_BOLD
	       "\t" MENU_HELP_FORMAT "\n");
	printf("\t" STYLE_BOLD MENU_CMD_HELP STYLE_NO_BOLD
	       "\t" MENU_HELP_HELP "\n");
	printf("\t" STYLE_BOLD MENU_CMD_LIST STYLE_NO_BOLD
	       "\t" MENU_HELP_LIST "\n");
	printf("\t" STYLE_BOLD MENU_CMD_READ STYLE_NO_BOLD
	       "\t" MENU_HELP_READ "\n");
	printf("\t" STYLE_BOLD MENU_CMD_WRITE STYLE_NO_BOLD
	       "\t" MENU_HELP_WRITE "\n");
	printf("\t" STYLE_BOLD MENU_CMD_QUIT STYLE_NO_BOLD
	       "\t" MENU_HELP_QUIT "\n");
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
	printf("\tInput file: ");
	datain = get_line();
	_dbgmsg("reading entries from \"%s\"", datain);
	read_all();
	free(datain);
}

void menu_format(void)
{
	printf(MENU_FORMAT);
}

void menu_write(void)
{
	printf("\tOutput file: ");
	dataout = get_line();
	_dbgmsg("write entries to \"%s\"", dataout);
	write_all();
	free(dataout);
}

char *get_line(void)
{
	char *input;
	char raw[MAX_LINE];
	fgets(raw, MAX_LINE, stdin);
	strtok(raw, "\n");
	raw[MAX_LINE] = '\0';
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
	} else if (strcmp(input, MENU_CMD_FORMAT) == 0) {
		command = FORMAT;
	} else if (strcmp(input, MENU_CMD_WRITE) == 0) {
		command = WRITE;
	} else if (strcmp(input, "\n") == 0) {
		command = ENTER;
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
	case HELP:	menu_help();		break;
	case ADD:	menu_add();		break;
	case LIST:	menu_list();		break;
	case QUIT:	menu_quit();		break;
	case CLEAR:	menu_clear();		break;
	case DELETE:	menu_delete();		break;
	case ABOUT:	menu_about();		break;
	case READ:	menu_read();		break;
	case FORMAT:	menu_format();		break;
	case WRITE:	menu_write();		break;
	case ENTER:	break;
	default:	_dbgerr("wrong syntax");
			printf(MENU_INVALID "\n");
			break;
	}
	return 0;
}
