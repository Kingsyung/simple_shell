#include "shell.h"

/**
 * initializeInfo - initializes info_t struct
 * @info: struct address
 */
void initializeInfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setupInfo - initializes info_t struct
 * @info: struct addresses
 * @av: argument vectors
 */
void setupInfo(info_t *info, char **av)
{
	int x = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
			}
		for (x = 0; info->argv && info->argv[x]; x++)
			;
		info->argc = x;

		replaceAlias(info);
		replaceVariables(info);
	}
}

/**
 * releaseInfo - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void releaseInfo(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeList(&(info->env));
		if (info->history)
			freeList(&(info->history));
		if (info->alias)
			freeList(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
