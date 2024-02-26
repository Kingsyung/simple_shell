#include "shell.h"

/**
 * obtainEnvironment - returns the string array copy of our environment
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
char **obtainEnvironment(info_t *info)
{
	if (!info->environment || info->envChanged)
	{
		info->environment = listToStrings(info->env);
		info->envChanged = 0;
	}

	return (info->environment);
}

/**
 * removeEnvironmentVariable - Removes environment variables
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @variable: the string environment variable property
 * Return: 1 on delete, 0 otherwise
 */

int removeEnvironmentVariable(info_t *info, char *variable)
{
	list_t *currentNode = info->env;
	size_t index = 0;
	char *p;

	if (!currentNode || !variable)
		return (0);

	while (currentNode)
	{
		p = startsWith(currentNode->str, variable);
		if (p && *p == '=')
		{
			info->envChanged = deleteNodeAtIndex(&(info->env), index);
			index = 0;
			currentNode = info->env;
			continue;
		}
		currentNode = currentNode->next;
		index++;
	}
	return (info->envChanged);
}

/**
 * setEnvironmentVariable - Initialize a new environment variable,
*                          or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @variable: the string environment variable property
 * @value: the string environment variable value
 * Return: Always 0
 */
int setEnvironmentVariable(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;
	while (node)
	{
		p = startsWith(node->str, variable);
		if (p && *p == '=')
			{
			free(node->str);
			node->str = buffer;
			info->envChanged = 1;
			return (0);
		}
		node = node->next;
	}
	addNodeEnd(&(info->env), buffer, 0);
	free(buffer);
	info->envChanged = 1;
	return (0);
}
