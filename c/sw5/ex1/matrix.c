/*
* matrix.c - Matrix creation
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

#include "matrix.h"

int _print_matrix(int **matrix, const int rows, const int cols);

int **create_matrix(const int rows, const int cols, const int init)
{
	int **matrix;

	int r;
	int c;

	r = 0;
	c = 0;

	matrix = (int **)malloc(rows*sizeof(int *)+1);
	matrix[rows] = NULL;
	if (matrix == NULL) {
		return NULL;
	}

	for(r = 0; r < rows; r++) {
		matrix[r] = (int *)malloc(cols*sizeof(int));
		if (matrix[r] == NULL) {
			while ((r-1) >= 0) {
				r = r-1;
				free(matrix[r]);
			}
			free(matrix);
			return NULL;
		}
		for(c = 0; c < cols; c++) {
			matrix[r][c] = init;
		}
	}

	_print_matrix(matrix, rows, cols);

	return matrix;
}

int _print_matrix(int **matrix, const int rows, const int cols)
{
	int r, c;

	r = rows;
	c = cols;

	#ifdef DEBUG
	printf("DEBUG: created %ix%i matrix\n", rows, cols);
	#endif
	for(r = 0; r < rows; r++) {
		printf("\t");
		for(c = 0; c < cols; c++) {
			printf("%i\t", matrix[r][c]);
		}
		printf("\n");
	}

	return 0;
}

int destroy_matrix(int **matrix)
{
	int ctr;
	ctr = 0;

	#ifdef DEBUG
		printf("DEBUG: destroying matrix\n");
	#endif

	/* _dbgmsg("destroying matrix"); */

	if (matrix == NULL) {
		return 0;
	}

	while (matrix[ctr] != NULL) {
		free(matrix[ctr]);
		ctr++;
	}

	free(matrix);

	return 0;
}
