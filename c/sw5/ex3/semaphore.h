/*
* semaphore.h - Semaphore
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
} SemaphorStates_t;

/**
 * Set the callback function that defines the time of each phase.
 * @param getPhaseTimePointer to function that returns the phase length in
 * seconds.
 *	The function gets as Parameter the current semaphore state.
 */
/* !!! To do !!! void setSemaphoreCallbackFunction(...); */
void setSemaphoreCallbackFunction(void* a);

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
