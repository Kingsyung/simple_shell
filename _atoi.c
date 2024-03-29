#include "shell.h"

/**
 * isInteractive - returns true if shell is in interactive mode
 * @shellInfo: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int isInteractive(info_t *shellInfo)
{
	return (isatty(STDIN_FILENO) && shellInfo->readfd <= 2);
}

/**
 * isDelimiter - checks if character is a delimiter.
 * @c: the char to check.
 * @delim: the delimiter string.
 * Return: 1 if true, 0 if false.
 */

int isDelimiter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);

	return (0);
}

/**
 * isAlpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int isAlpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * customAtoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int customAtoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
