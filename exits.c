#include "shell.h"

/**
 * strncpy - copies a string
 * @destination: the destination string to be copied to
 * @source: the source string
 * @n: the number of characters to be copied
 * Return: the concatenated string
 */

char *strncpy(char *destination, char *source, int n)
{
    int x;
    char *result = destination;
    x = 0;

    while (source[x] != '\0' && x < n - 1)
    {
        destination[x] = source[x];
        x++;
    }
    if (x < n)
    {
        while (x < n)
        {
            destination[x] = '\0';
            x++;
        }
    }
    return result;
}

/**
 * strncat - concatenates two strings
 * @destination: the first string
 * @source: the second string
 * @n: the maximum number of bytes to be used
 * Return: the concatenated string
 */

char *strncat(char *destination, char *source, int n)
{
    int x, y;
    char *result = destination;
    x = 0;
    y = 0;

    while (destination[x] != '\0')
        x++;
    while (source[y] != '\0' && y < n)
    {
        destination[x] = source[y];
        x++;
        y++;
    }
    if (y < n)
        destination[x] = '\0';
    return result;
}

/**
 * strchr - locates a character in a string
 * @string: the string to be parsed
 * @character: the character to look for
 * Return: a pointer to the first occurrence of the character in the string,
 * or NULL if the character is not found
 */

char *strchr(char *string, char character)
{
    do
    {
        if (*string == character)
            return string;
    } while (*string++ != '\0');
    return NULL;
}
