#include <stdio.h>
#include <stdlib.h>
#include "semaphore.h"

/**
 * Determins the length of each phase of the semaphor.
 * @param phase actuel phase
 * @param Time in ms for the corresponding phase
 */
int getPhaseTime(SemaphorState_t phase)
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

/**
 * Start the semaphor and defines with the the implementation of a callback
 * function the length of the various periods.
 */
int main(int argc, char** argv)
{
	/* !!! To do: Set callback function !!!
	setSemaphorCallbackFunction(...);
	*/

	printf("Starting the semaphor...\n");
	startSemaphore();

	// Let the semaphor run for 1 minute
	sleep(60);

	printf("Stopping the semaphor...\n");
	stopSemaphor();
	printf("Semaphor stopped... \n");

	return (EXIT_SUCCESS);
}
