#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _dmyhistory(info_t *info)
{
	dprint_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int dunset_alias(info_t *info, char *str)
{
	char *d, e;
	int dret;

	d = _dstrchr(str, '=');
	if (!d)
		return (1);
	e = *d;
	*d = 0;
	dret = ddelete_node_at_index(&(info->alias),
		dget_node_index(info->alias, dnode_starts_with(info->alias, str, -1)));
	*d = e;
	return (dret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int dset_alias(info_t *info, char *str)
{
	char *d;

	d = _dstrchr(str, '=');
	if (!d)
		return (1);
	if (!*++d)
		return (dunset_alias(info, str));

	dunset_alias(info, str);
	return (dadd_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * dprint_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int dprint_alias(list_t *node)
{
	char *d = NULL, *e = NULL;

	if (node)
	{
		d = _dstrchr(node->str, '=');
		for (e = node->str; e <= d; e++)
			_dputchar(*e);
		_dputchar('\'');
		_dputs(d + 1);
		_dputs("'\n");
		return (0);
	}
	return (1);
}

/**
 * _dmyalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _dmyalias(info_t *info)
{
	int d = 0;
	char *e = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			dprint_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (d = 1; info->argv[d]; d++)
	{
		e = _dstrchr(info->argv[d], '=');
		if (e)
			dset_alias(info, info->argv[d]);
		else
			dprint_alias(dnode_starts_with(info->alias, info->argv[d], '='));
	}

	return (0);
}
