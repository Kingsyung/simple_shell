#include "shell.h"

/**
 * bfree - frees pointers and NULLs the address
 * @ptr_addr: address of the pointers to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr_addr)
{
	if (ptr_addr && *ptr_addr)
	{
		free(*ptr_addr);
		*ptr_addr = NULL;
		return (1);
	}
	return (0);
}
