/*
 * main.c - Exercise 1, SW3
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
#include <string.h>
#include "list.h"



int main(int argc, char **argv)
{
    printf("-- Add entries\n");
    addEntry("Nino", "Ninux");
    addEntry("Dennis", "Ritchie");
    addEntry("Brian", "Kerninghan");
    addEntry("Linus", "Torvalds");
    addEntry("Richard", "Stallman");
    addEntry("Konrad", "Zuse");

    printf("-- Dump list\n");
    plist();

    printf("-- Remove list\n");
    delList();

    return 0;
}
