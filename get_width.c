#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * get_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int charr_j;
	int width = 0;

	for (charr_j = *i + 1; format[charr_j] != '\0'; charr_j++)
	{
		if (is_digit(format[charr_j]))
		{
			width *= 10;
			width += format[charr_j] - '0';
		}
		else if (format[charr_j] == '*')
		{
			charr_j++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = charr_j - 1;

	return (width);
}
