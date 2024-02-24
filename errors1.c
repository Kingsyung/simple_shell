#include "shell.h"

/**
 * errAtoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *  -1 on error
 */

int errAtoi(char *s)
{
	int x = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (x = 0;  s[x] != '\0'; x++)
	{
		if (s[x] >= '0' && s[x] <= '9')
		{
			result *= 10;
			result += (s[x] - '0');

			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * printError - prints an error message
 * @shellInfo: the parameter & return info struct
 * @errorMsg: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *         -1 on error
 */

void printError(ShellInfo *shellInfo, char *errorMsg)
{
	eputs(shellInfo->filename);
	eputs(": ");
	printDecimal(shellInfo->lineCount, STDERR_FILENO);
	eputs(": ");
	eputs(shellInfo->argv[0]);
	eputs(": ");
	eputs(errorMsg);
}

/**
 * printDecimal - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */

int printDecimal(int input, int fd)
{
	int (*putCharFunc)(char) = putchar;
	int x, count = 0;
	unsigned int absValue, current;

	if (fd == STDERR_FILENO)
		putCharFunc = eputchar;

	if (input < 0)
		{
		absValue = -input;
		putCharFunc('-');
		count++;
	}
	else
		absValue = input;

	current = absValue;

	for (x = 1000000000; i > 1; x /= 10)
	{
		if (absValue / x)
		{
			putCharFunc('0' + current / x);
			count++;
		}
		current %= x;
	}
	putCharFunc('0' + current);
	count++;
	return (count);
}

/**
 * convertNumber - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */

char *convertNumber(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do
	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * removeComments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */

void removeComments(char *buf)
{
	int x;

	for (x = 0; buf[x] != '\0'; x++)
		if (buf[x] == '#' && (!x || buf[x - 1] == ' '))
		{
			buf[x] = '\0';
			break;
		}
}


