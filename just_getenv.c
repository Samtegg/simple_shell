#include "shell.h"

/**
 * dget_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **dget_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = dlist_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _dunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _dunsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t di = 0;
	char *dp;

	if (!node || !var)
		return (0);

	while (node)
	{
		dp = dstarts_with(node->str, var);
		if (dp && *dp == '=')
		{
			info->env_changed = ddelete_node_at_index(&(info->env), di);
			di = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		di++;
	}
	return (info->env_changed);
}

/**
 * _dsetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _dsetenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *dp;

	if (!var || !value)
		return (0);

	buf = malloc(_dstrlen(var) + _dstrlen(value) + 2);
	if (!buf)
		return (1);
	_dstrcpy(buf, var);
	_dstrcat(buf, "=");
	_dstrcat(buf, value);
	node = info->env;
	while (node)
	{
		dp = dstarts_with(node->str, var);
		if (dp && *dp == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	dadd_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
