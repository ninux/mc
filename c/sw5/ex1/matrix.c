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

	matrix = (int **)calloc((rows+1), sizeof(int *));
	if (matrix == NULL) {
		_dbgerr("allocating memory failed");
		return NULL;
	} else {
		_dbgmsg("allocated memory for %i rows at <%i>", rows, matrix);
		matrix[rows] = NULL;
	}

	for(r = 0; r < rows; r++) {
		matrix[r] = (int *)malloc(cols*sizeof(int));
		#ifdef DEBUG
			if (r > MAX_ROWS) {
				free(matrix[r]);
				matrix[r] = NULL;
			}
		#endif
		if (matrix[r] == NULL) {
			_dbgerr("allocating memory failed");
			while ((r-1) >= 0) {
				r = r-1;
				_dbgnice("freeing already allocated "
					"column %i at <%i>", r+1, matrix[r]);
				free(matrix[r]);
			}
			free(matrix);
			_dbgnice("finished freeing");
			return NULL;
		} else {
			_dbgmsg("allocated memory for column %i at <%i>",
				r+1, matrix[r]);
			for(c = 0; c < cols; c++) {
				matrix[r][c] = init;
			}
		}
	}

	_print_matrix(matrix, rows, cols);

	return matrix;
}

int _print_matrix(int **matrix, const int rows, const int cols)
{
	if (matrix == NULL) {
		_dbgwarn("invalid matrix -> aborting print");
		return -1;
	}

	int r, c;

	r = rows;
	c = cols;

	_dbgmsg("created %ix%i matrix", rows, cols);

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

	_dbgmsg("freeing matrix from head to tail");

	if (matrix == NULL) {
		_dbgwarn("matrix is already empty");
		return 0;
	}

	while (matrix[ctr] != NULL) {
		_dbgmsg("freeing row %i at <%i>", ctr+1, matrix[ctr]);
		free(matrix[ctr]);
		ctr++;
	}

	free(matrix);
	_dbgnice("finished freeing");

	return 0;
}
