#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);
// Start procesing the variable argument list
	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			// Check if the character is not a '%', if it is not, add the character to the buffer and update buff_ind
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
			// Check if the buffer is full, if it is, print its contents and reset buff_ind
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{
			// Else, if the character is '%', process the format specifier
			// but first, print the buffer contents if it is not empty
			print_buffer(buffer, &buff_ind);
			// For the format specifier, get the flags, width, precision and size
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			// Go past the '%' and process the format specifier
			++i;
			// Then handle the format specifier and get the number of characters printed
			printed = handle_print(format, &i, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			// Bring the total number of characters printed up to date
			printed_chars += printed;
		}
	}
// In the buffer, print any remaining characters
	print_buffer(buffer, &buff_ind);
// Bring the processing of the variable argument list to an end
	va_end(list);
// Return the total number of characters printed
	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	// Print the contents of the buffer is it is not empty
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);
// To reuse the buffer, reset the buffer index ; buff_ind
	*buff_ind = 0;
}
