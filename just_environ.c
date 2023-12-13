#include "shell.h"

/**
 * _dmyenv - this function prints 
 * current environ.
 * @info: the Struct containing potential arg, used to maintain
 *          constant function prototype.
 * Return: its Always 0
 */
int _dmyenv(info_t *info)
{
	dprint_list_str(info->env);
	return (0);
}

/**
 * _dgetenv - this function gets 
 * the value of environ var.
 * @info: the Struct containing potential arg, used to maintain
 * @name: the env var name
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
 * _dmysetenv - this function Initializes a new environ var,
 * or modify an existing one
 * @info: this Struct containing potential arg, used to maintain
 * constant function prototype.
 *  Return: Always returns 0
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
 * _dmyunsetenv - this function Removes an environment variable
 * @info: this Struct contains potential arg, 
 * used to maintain
 * constant function prototype.
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
 * dpopulate_env_list - this function populates the env linked list
 * @info: this function Structure contains potential arg. 
 * used to maintain
 * constant function prototype.
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
