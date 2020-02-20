/*
 File:              recursion.c
 Purpose:           Exercises for CPSC259 lab 4
 Author:			Or Bahari and Emily
 Student #s:		51277200 and 12345678
 CS Accounts:		i0k2b and b2b2
 Date:				23.10.18
 */

/******************************************************************
 PLEASE EDIT THIS FILE

 Comments that start with // should be replaced with code
 Comments that are surrounded by * are hints
 ******************************************************************/


/* Preprocessor directives */	
#include <stdio.h>
#include <stdlib.h>
#include "recursion.h"

/*
 Main function drives the program.
 PRE:       NULL (no pre-conditions)
 POST:      NULL (no side-effects)
 RETURN:    IF the program exits correctly
            THEN 0 ELSE 1
 */
int main (void)
{
	
	printf("Testing output from draw_ramp() function:\n");
	printf("\ndraw_ramp(1):\n");
	draw_ramp(1);
	printf("\ndraw_ramp(2):\n");
	draw_ramp(2);
	printf("\ndraw_ramp(3):\n");
	draw_ramp(3);
	printf("\ndraw_ramp(4):\n");
	draw_ramp(4);
	printf("\ndraw_ramp(5):\n");
	draw_ramp(5);
	/*
	printf("5^3=%d\n", calculate_power(-5, 3));
	printf("number of digit in 1234 is:%d\n",count_digits(1234));
	printf("the length of:emily the cutest is:%d\n", string_length("emily the cutest"));
	printf("ispalindrom:%d\n", is_palindrome("aBba",string_length("aBba")));
	*/
	system("pause");
	return 0;
}

/*
 Calculates the power.
 PARAM:     base is an integer
 PARAM:     power is an integer
 PRE:       power >= 0
 PRE:       base != 0
 RETURN:    base^power
 */
int calculate_power(int base, int power)
{
	if (power < 0) return -1; //error
	if (power == 0) return 1;
	return base*calculate_power(base, power - 1);
}

/*
 Returns the number of digits in an integer
 PARAM:     number is an integer
 PRE:       0 < number <= INT_MAX
 RETURN:    the number of digits in the number
 */
int count_digits(int number)
{
	if (number == 0) return 0;
	return 1 + count_digits(number / 10);
}

/*
 Returns the length of the specified string.
 PARAM:  string, a pointer to an array of char
 PRE:    the string pointer is not a dangling pointer
 RETURN: the length of the string passed as a parameter  
 */
int string_length( char * string )
{
	if (*string == '\0') return 0;
	return 1 + string_length(string + 1);
}

/*
 Determines if a string is a palindrome.  DOES NOT skip spaces!
 For example, 
 ""     -> returns 1 (an empty string is a palindrome)
 "the"  -> returns 0
 "abba" -> returns 1
 "Abba" -> returns 0
 "never odd or even" -> returns 0
 PARAM:  string, a pointer to an array of char
 PARAM:  string_length, the length of the string
 PRE:    the string pointer is not a dangling pointer
 PRE:    string_length is the correct length of the string
 RETURN: IF string is a palindrome
         THEN 1
		 END 0
 */
int is_palindrome(char * string, int string_length)
{
	if (string_length == 0 || string_length==1) return 1;
	if (string[0] != string[string_length - 1]) return 0;
	return is_palindrome(string + 1, string_length - 2);
}

/*
 Draws a ramp.  The length of the longest rows is specified by the parameter.
 PARAM:     number, an integer
 PRE:       number >= 1
 POST:      draws a ramp whose height is the specified number
 */
void draw_ramp( int number ) 
{
	if (number == 1) return draw_row(1);
	draw_row(number);
	draw_ramp(number - 1);
	draw_row(number);
	 
}

/*
 Draws a row of asterisks of the specified length
 PARAM: size, an integer
 PRE:   size >= 1
 POST:  prints a row of asterisks of specified length to standard output
 */
void draw_row( int size )
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("*");
	}
	printf("\n");
}