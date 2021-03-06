/*
* semaphore.c - Semaphore
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
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "semaphore.h"

/* !!! To do: Define a variable getPhaseTimeFunction of type
   'pointer-to-function' for the callback function and set it to NULL */
int (*getPhaseTimeFunction)(SemaphorStates_t) = NULL;

static int threadRunning = 0;
static SemaphorStates_t state = RED;
static pthread_t threadId;
static pthread_attr_t threadAttr;

/**
 * Print current thread state
 */
static void printThreadState(int sleepTime)
{
	char stateStr[64];

	switch (state) {
	case GREEN:		strcpy(stateStr, "GREEN");		break;
	case GREEN_BLINKING:	strcpy(stateStr, "GREEN BLINKING");	break;
	case YELLOW:		strcpy(stateStr, "YELLOW");		break;
	case RED:		strcpy(stateStr, "RED");		break;
	default:		strcpy(stateStr, "UNDEFINED");		break;
	}
	printf("The semaphor is %-14s for %2d seconds\n", stateStr, sleepTime);
	fflush(stdout);
}

static void* threadFunction(void* args)
{
	int sleepTime = 2;
	printThreadState(sleepTime);
	sleep(sleepTime);

	while (threadRunning) {
		switch (state) {
		case GREEN:		state = GREEN_BLINKING;	break;
		case GREEN_BLINKING:	state = YELLOW;		break;
		case YELLOW:		state = RED;		break;
		case RED:		state = GREEN;		break;
		default: /* Should not happen, but added error recovery */
					state = RED;		break;
		}

/* !!! To do: Call here the callback function to get the sleep time */
		if (getPhaseTimeFunction != NULL)
		{
			sleepTime = getPhaseTimeFunction(state);
		} else {
			sleepTime = 1;
		}
		printThreadState(sleepTime);
		sleep(sleepTime);
	}
	printf("Semaphor thread stopped\n");

	return NULL;
}


/* !!! To do !!! */
void setSemaphorCallbackFunction(void (*a))
{
	getPhaseTimeFunction = a;
}

void startSemaphore()
{
	threadRunning = 1;

	/* start thread */
	pthread_attr_init(&threadAttr);
	/* the third argument is a pointer to the thread function */
	pthread_create(&threadId, &threadAttr, threadFunction, NULL);
}

void stopSemaphor()
{
	threadRunning = 0;

	/* wait until thread is finished */
	pthread_join(threadId, NULL);
	pthread_attr_destroy(&threadAttr);
}
