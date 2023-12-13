#include "shell.h"

/**
 * dis_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int dis_chain(info_t *info, char *buf, size_t *p)
{
	size_t dj = *p;

	if (buf[dj] == '|' && buf[dj + 1] == '|')
	{
		buf[dj] = 0;
		dj++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[dj] == '&' && buf[dj + 1] == '&')
	{
		buf[dj] = 0;
		dj++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[dj] == ';') /* found end of this command */
	{
		buf[dj] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = dj;
	return (1);
}

/**
 * dcheck_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void dcheck_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t dj = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			dj = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			dj = len;
		}
	}

	*p = dj;
}

/**
 * dreplace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int dreplace_alias(info_t *info)
{
	int di;
	list_t *dnode;
	char *dp;

	for (di = 0; di < 10; di++)
	{
		dnode = dnode_starts_with(info->alias, info->argv[0], '=');
		if (!dnode)
			return (0);
		free(info->argv[0]);
		dp = _dstrchr(dnode->str, '=');
		if (!dp)
			return (0);
		dp = _dstrdup(dp + 1);
		if (!dp)
			return (0);
		info->argv[0] = dp;
	}
	return (1);
}

/**
 * dreplace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int dreplace_vars(info_t *info)
{
	int di = 0;
	list_t *dnode;

	for (di = 0; info->argv[di]; di++)
	{
		if (info->argv[di][0] != '$' || !info->argv[di][1])
			continue;

		if (!_dstrcmp(info->argv[di], "$?"))
		{
			dreplace_string(&(info->argv[di]),
				_dstrdup(dconvert_number(info->status, 10, 0)));
			continue;
		}
		if (!_dstrcmp(info->argv[di], "$$"))
		{
			dreplace_string(&(info->argv[di]),
				_dstrdup(dconvert_number(getpid(), 10, 0)));
			continue;
		}
		dnode = dnode_starts_with(info->env, &info->argv[di][1], '=');
		if (dnode)
		{
			dreplace_string(&(info->argv[di]),
				_dstrdup(_dstrchr(dnode->str, '=') + 1));
			continue;
		}
		dreplace_string(&info->argv[di], _dstrdup(""));

	}
	return (0);
}

/**
 * dreplace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int dreplace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
