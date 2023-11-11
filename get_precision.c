#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * get_precision - Writing a fxn that calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */

int get_precision(const char *format, int *i, va_list list)
{
	int charr_j = *j + 1;
	int precision = -1;

	if (format[charr_j] != '.')
		return (precision);

	precision = 0;

	for (charr_j += 1; format[charr_j] != '\0'; charr_j++)
	{
		if (is_digit(format[charr_j]))
		{
			precision *= 10;
			precision += format[charr_j] - '0';
		}
		else if (format[charr_j] == '*')
		{
			charr_j++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*j = charr_j - 1;

	return (precision);
}
