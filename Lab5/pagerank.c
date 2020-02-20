/*
File:              pagerank.c
Purpose:           Exercises for CPSC259 lab 5
Author:			Or Bahari and Emily
Student #s:		51277200 and 41724148
CS Accounts:		i0k2b and r8u9a
Date:				2018-11-27
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"

#define  BUFSIZE 256
#define FILEWEB "web.txt"
FILE       * webfile = NULL;

/* Function prototypes */
int get_matrix_dimension(FILE * webfile);
double** parse_matrix(FILE * file, int dimension);
void  deleteSpaces(char src[], char dst[]);

int main(void)
{
	int          dimension = 0;
	int          error = 0;
	double **connectivity_matrix = NULL;
	double *PR = NULL;
	
	error = fopen_s(&webfile, FILEWEB, "r");
	if (error)
	{
		fprintf(stderr, "Unable to open file: %s\n", FILEWEB);
		system("pause");
		return 1;
	}
	if (webfile)
	{
		dimension = get_matrix_dimension(webfile);
		if (dimension <= 0)
		{
			printf("incorrect dimension");
			return;
		}
	}
	
	connectivity_matrix = parse_matrix(webfile, dimension);

	/* Variables */
	Engine *ep = NULL; // A pointer to a MATLAB engine object
	mxArray *con_mat = NULL;
	char buffer[BUFSIZE + 1];
	int i;
	double *con_mat2;

	if (!(ep = engOpen(NULL)))
	{
		fprintf(stderr, "\nCan't start MATLAB engine\n");
		system("pause");
		return 1;
	}

	con_mat = mxCreateDoubleMatrix(dimension, dimension, mxREAL);

	//A trick to copy dynamic allocated array
	con_mat2 = mxGetPr(con_mat);
	for (i = 0; i < dimension; i++)
	{
		memcpy(con_mat2, connectivity_matrix[i], dimension * sizeof(double));
		con_mat2 += dimension;
	}

	//put var in matlab
	if (engPutVariable(ep, "c_mat", con_mat))
	{
		fprintf(stderr, "\nCannot write con_mat to MATLAB \n");
		system("pause");
		exit(1); // Same as return 1;
	}

	//The 14 'mgaic' commands
	engEvalString(ep, "[rows, columns] = size(c_mat);");
	engEvalString(ep, "dimension = size(c_mat, 1);");
	engEvalString(ep, "columnsums = sum(c_mat, 1);");
	engEvalString(ep, "p = 0.85");
	engEvalString(ep, "zerocolumns = find(columnsums~=0) ;");
	engEvalString(ep, "D = sparse( zerocolumns, zerocolumns, 1./columnsums(zerocolumns), dimension, dimension) ;");
	engEvalString(ep, "StochasticMatrix = c_mat * D ;");
	engEvalString(ep, "[row, column] = find(columnsums==0) ;");
	engEvalString(ep, "StochasticMatrix(:, column) = 1./dimension; ");
	engEvalString(ep, "Q = ones(dimension, dimension) ;");
	engEvalString(ep, "TransitionMatrix = p * StochasticMatrix + (1 - p) * (Q/dimension) ;");
	engEvalString(ep, "PageRank = ones(dimension, 1) ;");
	engEvalString(ep, "for i = 1:100 PageRank = TransitionMatrix * PageRank; end ;");
	engEvalString(ep, "PageRank = PageRank / sum(PageRank) ;");

	if (engOutputBuffer(ep, buffer, BUFSIZE)) {
		fprintf(stderr, "\nCan't create buffer for MATLAB output\n");
		system("pause");
		return 1;
	}
	buffer[BUFSIZE] = '\0';
	
	printf("PageRank is:\n");
	printf("\t\tNode\t\tRank\n");
	printf("\t\t----\t\t----\n");
	if ((PR = engGetVariable(ep, "PageRank")) == NULL)
	{
		fprintf(stderr, "\nFailed to retrieve 'PageRank' vector\n");
		system("pause");
		exit(1);
	}
	else
	{
		size_t sizeOfResult = mxGetNumberOfElements(PR);
		size_t i = 0;
		int j = 0;
		for (i = 0; i < sizeOfResult; ++i)
		{
			
			j = j + 1;
			printf("\t\t%d\t\t%f\n", j,*(mxGetPr(PR) + i));
		}
	}
	
	//Freeing memory
	mxDestroyArray(con_mat);
	con_mat = NULL;
	if (engClose(ep))
	{
		fprintf(stderr, "\nFailed to close MATLAB engine\n");
	}

	system("pause"); // So the terminal window remains open long enough for you to read it
	return 0; // Because main returns 0 for successful completion
}


//We assume the connection matrix is a square matrix
int get_matrix_dimension(FILE* file)
{
	int  dimension = 0;
	char line_buffer[BUFSIZE];
	fgets(line_buffer, BUFSIZE, file);
	deleteSpaces(line_buffer, line_buffer);
	dimension = strlen(line_buffer);
	fseek(file, 0, SEEK_SET);
	if (strchr(line_buffer, '\r') != NULL)
	{  // deleteSpaces strips the \n anyway and puts 0 at the end so its different than the case in maze takeHome
		return dimension - 1;
	}
	else
	{
		return dimension;
	}
}


//A function to remove spaces from string for fun..
void  deleteSpaces(char src[], char dst[])
{
	// src is supposed to be zero ended
	// dst is supposed to be large enough to hold src
	int s, d = 0;
	for (s = 0; src[s] != 0 && src[s] != '\n'; s++)
		if (src[s] != ' ') {
			dst[d] = src[s];
			d++;
		}
	dst[d] = 0;
	dst[d + 1] = '\n';
}

//parse the connection matrix and return it
double** parse_matrix(FILE * file, int dimension)
{
	char         line_buffer[BUFSIZE];
	int          row = 0, column = 0;
	double ** matrix = NULL;

	/* Allocates memory for correctly-sized maze */
	matrix = (double **)calloc(sizeof(double*), dimension);

	for (row = 0; row < dimension; ++row) {
		matrix[row] = (double*)calloc(sizeof(double), dimension);
	}
	row = 0;
	while (fgets(line_buffer, BUFSIZE, file))
	{
		deleteSpaces(line_buffer, line_buffer);
		for (column = 0; column < dimension; ++column)
		{
			//filling matrix with reverse indices because this is what matlab likes...
			matrix[column][row] = (line_buffer[column] - '0');
		}
		row++;
	}
	return matrix;
}