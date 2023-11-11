#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/************************* PRINT CHAR *************************/

/**
 * print_char - Writing a fxn that prints a char
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 *
 */

int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/************************* PRINT A STRING *************************/

/**
 * print_string - Writing a fxn that prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 *
 */

int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, w;
	char *swt = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (swt == NULL)
	{
		swt = "(null)";
		if (precision >= 6)
			swt = "      ";
	}

	while (swt[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &swt[0], length);
			for (w = width - length; w > 0; w--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (w = width - length; w > 0; w--)
				write(1, " ", 1);
			write(1, &swt[0], length);
			return (width);
		}
	}

	return (write(1, swt, length));
}

/************************* PRINT PERCENT SIGN *************************/

/**
 * print_percent - Writing a fxn that prints a percent sign
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 *
 */

int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Writing a fxn that print int
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 *
 */

int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int w = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int digit;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[w--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	digit = (unsigned long int)n;

	if (n < 0)
	{
		digit = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (digit > 0)
	{
		buffer[w--] = (digit % 10) + '0';
		digit /= 10;
	}

	w++;

	return (write_number(is_negative, w, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Writing a fxn that prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 *
 */

int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int j, k, w, digit;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	j = va_arg(types, unsigned int);
	k = 2147483648; /* (2 ^ 31) */
	a[0] = j / k;
	for (w = 1; w < 32; w++)
	{
		k /= 2;
		a[w] = (j / k) % 2;
	}
	for (w = 0, digit = 0, count = 0; w < 32; w++)
	{
		digit += a[w];
		if (digit || w == 31)
		{
			char z = '0' + a[w];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
