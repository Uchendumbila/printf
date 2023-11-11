#include "main.h"
#include <stdio.h>
#include <stdlib.h>

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 *
 */

int _printf(const char *format, ...)
{
	int w, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list charr;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(charr, format);

	for (w = 0; format && format[w] != '\0'; w++)
	{
		if (format[w] != '%')
		{
			buffer[buff_ind++] = format[w];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &w);
			width = get_width(format, &w, charr);
			precision = get_precision(format, &w, charr);
			size = get_size(format, &w);
			++w;
			printed = handle_print(format, &w, charr, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(charr);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 *
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
