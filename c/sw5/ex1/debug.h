/*
* debug.h - Debug utilities
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

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdlib.h>

#define MEMORY_LIMIT 1000000

#ifdef DEBUG
#define _dbgmsg(MESSAGE, ...) printf("<DEBUG>: " MESSAGE "\n", ##__VA_ARGS__)
#else
#define _dbgmsg(MESSAGE, ...) do {} while(0)
#endif

#ifdef DEBUG
#define _dbgerr(MESSAGE, ...) printf("<DEBUG>: %s" MESSAGE "%s\n", _RED_, \
	##__VA_ARGS__, _RESET_)
#else
#define _dbgerr(MESSAGE, ...) do {} while(0)
#endif

#ifdef DEBUG
#define _dbgwarn(MESSAGE, ...) printf("<DEBUG>: %s" MESSAGE "%s\n", _YELLOW_, \
	##__VA_ARGS__, _RESET_)
#else
#define _dbgwarn(MESSAGE, ...) do {} while(0)
#endif

#ifdef DEBUG
#define _dbgnice(MESSAGE, ...) printf("<DEBUG>: %s" MESSAGE "%s\n", _GREEN_, \
	##__VA_ARGS__, _RESET_)
#else
#define _dbgnice(MESSAGE, ...) do {} while(0)
#endif

#ifdef DEBUG
#define _dbginfo() printf("<DEBUG>: "		\
			  "build information:"	\
			  "\n\t Date\t%s"	\
			  "\n\t Time\t%s "	\
			  "\n\t GCC\t%s"	\
			  "\n\t C rev\t%i\n",	\
			  __DATE__,		\
			  __TIME__,		\
			  __VERSION__,		\
			  __STDC_VERSION__)
#else
#define _dbginfo()
#endif

#define _RED_		"\x1b[31m"
#define _GREEN_		"\x1b[32m"
#define _YELLOW_	"\x1b[33m"
#define _BLUE_		"\x1b[34m"
#define _RESET_		"\x1b[0m"

#endif /* DEBUG_H */
