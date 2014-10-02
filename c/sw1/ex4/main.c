#include <stdio.h>
#include <stdlib.h>
#include <ninux.h>

int main(int argc, char** argv)
{
	char ch;
	do {
		printf("Welcome to c coding\n");
		printf("Please select a menu item:\n");
		show_options();
		show_selection(ch = get_input());
	} while(ch != 'Q');
	return(0);
}
