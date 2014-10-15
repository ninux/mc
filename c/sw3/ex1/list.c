/*
 * list.c - Exercise 1, SW2
 *
 * Copyright (C) 2014 Ervin Mazlagic <nino.ninux@gmail.com>
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as ndet [-Wuninitialized]
 [ninux@t430 ex1]$ make clean all
 published by
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

typedef struct entry *entry_ptr_t;

typedef struct /*name*/ {
    char *first;
    char *last;
} name_t;

typedef struct entry {
    name_t *name;
    //entry_ptr_t *next; !!!!!!!!
    entry_ptr_t next;
} entry_t;

static entry_ptr_t head = NULL;

static name_t* createName(char *firstName, char *lastName);
static entry_ptr_t createEntry(name_t* pName);
static void addToList(entry_ptr_t pEle);
static void printAndAdvance(entry_ptr_t pEle, int nr);
static void deleteBackwards(entry_ptr_t pEle, int nr);

bool addEntry(char *first_name, char *last_name)
{
    name_t* pName;
    entry_ptr_t pEle;
    pName = createName(first_name, last_name);
    if (NULL != pName) {
        pEle = createEntry(pName);
        if (NULL != pEle) {
            addToList(pEle);
            return true;
        }
    }
    return false;
}

int plist(void)
{
    printAndAdvance(head, 0);
    return 0;
}

void delList(void)
{
    deleteBackwards(head, 0);
    head = NULL;
}

static name_t* createName(char *firstName, char *lastName)
{
    name_t* p_name;

    p_name = (name_t*)malloc(sizeof(name_t));
    if (NULL == p_name){
        return NULL;
    }
    p_name->first = malloc(strlen(firstName));
    if (NULL == p_name->first) {
        free(p_name);
        return NULL;
    }
    p_name->last = malloc(strlen(lastName));
    if (NULL == p_name->last) {
        free(p_name->first);
        free(p_name);
        return NULL;
    }

    strcpy(p_name->first, firstName);
    strcpy(p_name->last, lastName);

    return p_name;
}

static entry_ptr_t createEntry(name_t* pName)
{
    entry_ptr_t pEntry;

    //!!!!!!!!!!!!!!!!! ERROR
    //pEntry = malloc(sizeof(name) + sizeof(entry_ptr_t));
    pEntry = (entry_ptr_t)malloc(sizeof(entry_t));
    if (NULL == pEntry) {
        return NULL;
    }

    pEntry->name = pName;
    pEntry->next = NULL;

    return pEntry;
}

static void addToList(entry_ptr_t pEle)
{
    //insert front
    pEle->next = head;
    head = pEle;
}

static void printAndAdvance(entry_ptr_t pEle, int nr)
{
    if (NULL != pEle) {
        printf("Element Nr: %3d; ", nr);
        printf("  %s %s\n", pEle->name->first, pEle->name->last);
        printAndAdvance(pEle->next, nr + 1);
    }
}

static void deleteBackwards(entry_ptr_t pEle, int nr)
{
    if (NULL != pEle) {
        deleteBackwards(pEle->next, nr + 1);
        printf("REMOVE Element Nr: %3d; ", nr);
        printf("  %s %s\n", pEle->name->first, pEle->name->last);
        free(pEle->name->first);
        free(pEle->name->last);
        free(pEle->name);
        free(pEle);
    }
}
