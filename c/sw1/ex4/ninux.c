#define SELECT "Select menu item "
#define SELECTION "Changing to menu item --> "

#define OPTION_1 'A'
#define OPTION_2 'B'
#define OPTION_3 'C'

#define OPTION_ERROR "Sorry, invalid option"

#include <stdio.h>
#include <stdlib.h>


int do_a(void)
{
	printf("%s%c\n", SELECT, OPTION_1);
	return(0);
}

int do_b(void)
{
	printf("%s%c\n", SELECT, OPTION_2);
	return(0);
}

int do_c(void)
{
	printf("%s%c\n", SELECT, OPTION_3);
	return(0);
}

int show_options(void)
{
	printf("\t%c\n", OPTION_1);
	printf("\t%c\n", OPTION_2);
	printf("\t%c\n", OPTION_3);
	return(0);
}

char get_input()
{
	char input;
	while(!isalpha (input = getchar())){
		/* NO-OP */
	}
	input = toupper(input);
	return(input);
}

int show_selection(char option)
{
	switch(option){
	case OPTION_1:
		printf("%s%c\n", SELECTION, OPTION_1);
		break;
	case OPTION_2:
		printf("%s%c\n", SELECTION, OPTION_2);
		break;
	case OPTION_3:
		printf("%s%c\n", SELECTION, OPTION_3);
		break;
	default:
		printf("%s\n", OPTION_ERROR);
		break;
	}
}
