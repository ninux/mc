/** Implementation of a semaphor with a thread. Uses the POSIX library. */

#include <stdio.h>
#include <pthread.h>
#include "semaphore.h"

/* !!! To do: Define a variable getPhaseTimeFunction of type
   'pointer-to-function' for the callback function and set it to NULL */

static int threadRunning = 0;
static SemaphoreStates_t state = RED;
static pthread_t	threadID;	// Thread stuff
static pthread_attr_t	threadAttr;

/**
 * Print current thread state
 */
static void printThreadState(int sleepTime)
{
	char stateStr[64];

	switch (state) {
		case GREEN:		strcpy(stateStr, "GREEN"); break;
		case GREEN_BLINKING:	strcpy(stateStr, "GREEN BLINKING"); break;
		case YELLOW:		strcpy(stateStr, "YELLOW"); break;
		case RED:		strcpy(stateStr, "RED"); break;
		default:		strcpy(stateStr, "UNDEFINED"); break;
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
			case GREEN:		state = GREEN_BLINKING; break;
			case GREEN_BLINKING:	state = YELLOW; break;
			case YELLOW:		state = RED; break;
			case RED:		state = GREEN; break;
			default: // Should not happen, but added error recovery
						state = RED; break;
		}

/* !!! To do: Call here the callback function to get the sleep time
		if (getPhaseTimeFunction != NULL)
		{
			sleepTime = ...;
*/
		printThreadState(sleepTime);
		sleep(sleepTime);
	}
	printf("Semaphor thread stopped\n");

	return NULL;
}


/* !!! To do !!!
void setSemaphorCallbackFunction(...)
{
	getPhaseTimerFunction = 
}
*/

void startSemaphore()
{
	threadRunning = 1;

	// Thread starten
	pthread_attr_init(&threadAttr);
	// Hier wird als drittes Argument ein Zeiger auf die Thread-Funktion übergeben.
	pthread_create(&threadId, &threadAttr, threadFunction, NULL);
}

void stopSemaphor()
{
	threadRunning = 0;

	// wait until thread is finished
	pthread_join(threadId, NULL);
	pthread_attr_destroy(&threadAttr);
}
