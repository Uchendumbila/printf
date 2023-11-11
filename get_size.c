#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * get_size - Writing a fxn that calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @j: List of arguments to be printed.
 *
 * Return: Precision.
 */

int get_size(const char *format, int *j)
{
	int charr_j = *j + 1;
	int size = 0;

	if (format[charr_j] == 'l')
		size = S_LONG;
	else if (format[charr_j] == 'h')
		size = S_SHORT;

	if (size == 0)
		*j = charr_j - 1;
	else
		*j = charr_j;

	return (size);
}
