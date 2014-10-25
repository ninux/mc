#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

/**
 * Implementation of a semaphor with a thread.
 * Uses a callback function to define the various times.
 */

typedef enum SemaphoreStates_ {
	GREEN = 1,
	GREEN_BLINKING,
	YELLOW,
	RED
} Semaphorestates_t;

/**
 * Set the callback function that defines the time of each phase.
 * @param getPhaseTimePointer to function that returns the phase length in
 * seconds.
 *	The function gets as Parameter the current semaphore state.
 */
/* !!! To do !!! void setSemaphoreCallbackFunction(...); */

/**
 * Starts the semaphor.
 * Within a thread, the semaphore changes its state from GREEN to GREEN_BLINKING
 * to YELLOW to RED to GREEN to ...
 * After each state change, the callbackfunction defined by
 * setCallbackFunction(...) will be called to get the length of the
 * corresponding phase.
 */
void startSemaphore();

/**
 * Stop the semaphor.
 */
void stopSemaphor();

#endif /* _SEMAPHORE_H */
