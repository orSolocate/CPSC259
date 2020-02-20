/*
File:         tide_analyzer.h
Purpose:      Contains prototypes
Author:			  Or Bahari and Ocean Li
Student #s:		51277200 and 12033312
CS Accounts:  i0k2b and o5m1b
Date:				  26.9.18
*/

/********************************************************************
YOU MAY EDIT THIS FILE (BUT YOU DON'T NEED TO)
******************************************************************/

#pragma once

/* Insert function prototypes here */
FILE * open_file(FILE * file_pointer, char * fileName, char * mode);
void process_file(double array_to_populate[], FILE * pointer_to_data_file);