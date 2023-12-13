#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _dmyenv(info_t *info)
{
	dprint_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_dgetenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *d;

	while (node)
	{
		d = dstarts_with(node->str, name);
		if (d && *d)
			return (d);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _dmysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_deputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_dsetenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _dmyunsetenv(info_t *info)
{
	int d;

	if (info->argc == 1)
	{
		_deputs("Too few arguements.\n");
		return (1);
	}
	for (d = 1; d <= info->argc; d++)
		_dunsetenv(info, info->argv[d]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int dpopulate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t d;

	for (d = 0; environ [d]; d++)
		dadd_node_end(&node, environ[d], 0);
	info->env = node;
	return (0);
}
