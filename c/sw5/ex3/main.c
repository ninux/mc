/*
* main.c - Main program
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
#include "semaphore.h"

int getPhaseTime(SemaphorStates_t phase)
{
	int rc = 1;

	switch (phase) {
		case GREEN:		rc = 6; break;
		case GREEN_BLINKING:	rc = 2; break;
		case YELLOW:		rc = 2; break;
		case RED:		rc = 10; break;
		default: break;
	}
	return rc;
}

int main(int argc, char** argv)
{
	/* !!! To do: Set callback function !!! */
	setSemaphorCallbackFunction(&getPhaseTime);

	printf("Starting the semaphor...\n");
	startSemaphore();

	/* Let the semaphor run for 1 minute */
	sleep(60);

	printf("Stopping the semaphor...\n");
	stopSemaphor();
	printf("Semaphor stopped... \n");

	return (EXIT_SUCCESS);
}
