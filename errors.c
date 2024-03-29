#include "shell.h"

/**
 * eputs - prints an input string
 * @str: the string to be printed
 * Return: Nothing
 */

void eputs(char *str)
{
	int x = 0;

	if (!str)
		return;

	while (str[x] != '\0')
	{
		eputchar(str[x]);
		x++;
	}
}

/**
 * eputchar - writes character c to stderr
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int eputchar(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}

/**
 * putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The file descriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int putfd(char c, int fd)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(fd, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}

/**
 * putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of chars put
 */

int putsfd(char *str, int fd)
{
	int x = 0;

	if (!str)
		return (0);

	while (*str)
	{
		x += putfd(*str++, fd);
		}
	return (x);
}
