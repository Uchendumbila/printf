#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Writing a fxn that prints the value of a pointer variable
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 *
 */

int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_charr;
	char map_to[] = "0123456789abcdef";
	void *charr = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (charr == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_charr = (unsigned long)charr;

	while (num_charr > 0)
	{
		buffer[ind--] = map_to[num_charr % 16];
		num_charr /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Writing a fxn that prints ascii codes
 * in hexa of non printable chars
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 *
 */

int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int w = 0, offset = 0;
	char *swt = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (swt == NULL)
		return (write(1, "(null)", 6));

	while (swt[w] != '\0')
	{
		if (is_printable(swt[w]))
			buffer[w + offset] = swt[w];
		else
			offset += append_hexa_code(swt[w], buffer, w + offset);

		w++;
	}

	buffer[w + offset] = '\0';

	return (write(1, buffer, w + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Writing a fxn that prints reverse string.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 *
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *swt;
	int w, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	swt = va_arg(types, char *);

	if (swt == NULL)
	{
		UNUSED(precision);

		swt = ")Null(";
	}
	for (w = 0; swt[w]; w++)
		;

	for (w = w - 1; w >= 0; w--)
	{
		char z = swt[w];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Writing a fxn that print a string in rot13.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 *
 */

int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char m;
	char *swt;
	unsigned int w, n;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	swt = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (swt == NULL)
		swt = "(AHYY)";
	for (w = 0; swt[w]; w++)
	{
		for (n = 0; in[n]; n++)
		{
			if (in[n] == swt[w])
			{
				m = out[n];
				write(1, &m, 1);
				count++;
				break;
			}
		}
		if (!in[n])
		{
			m = swt[w];
			write(1, &m, 1);
			count++;
		}
	}
	return (count);
}
