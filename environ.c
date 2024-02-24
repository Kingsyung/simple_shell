#include "shell.h"

/**
 * myEnv - prints the current environment
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */

int myEnv(ShellInfo *shellInfo)
{
	printListStr(shellInfo->environment);
	return (0);
}

/**
 * getEnv - gets the value of an environment variable
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * @name: env var name
 * Return: the value
 */

char *getEnv(ShellInfo *shellInfo, const char *name)
{
	ListNode *node = shellInfo->environment;
	char *p;

	while (node)
	{
		p = startsWith(node->str, name);

		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * mySetEnv - Initialize a new environment variable,
 * or modify an existing one
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */

int mySetEnv(ShellInfo *shellInfo)
{
	if (shellInfo->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (setEnv(shellInfo, shellInfo->argv[1], shellInfo->argv[2]))
		return (0);
	return (1);
}

/**
 * myUnsetEnv - Remove an environment variable
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */

int myUnsetEnv(ShellInfo *shellInfo)
{
	int i;

	if (shellInfo->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= shellInfo->argc; i++)
		unsetEnv(shellInfo, shellInfo->argv[i]);
	return (0);
}

/**
 * populateEnvList - populates env linked list
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */

int populateEnvList(ShellInfo *shellInfo)
{
	ListNode *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addNodeEnd(&node, environ[i], 0);
	shellInfo->environment = node;
	return (0);
}

