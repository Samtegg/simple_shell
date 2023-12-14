#include "shell.h"

/**
 * dis_chain - this function test
 * current char in buf is chain delimeter
 * @info: param struct
 * @buf: char buf
 * @p: the address current position in buf
 *
 * Return: this 1 if chain delimeter, 0
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
 * dcheck_chain - this function checks
 * should continue chain based last status
 * @info: param struct
 * @buf: char buf
 * @p: address current position in buf
 * @i: the start position in buf
 * @len: the len of buf
 *
 * Return: the Void
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
 * dreplace_alias - this function replaces
 * aliases in tokenized string
 * @info: param struct
 *
 * Return: this  1 if replaced, 0
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
 * dreplace_vars - this function replaces
 * vars in tokenized string
 * @info: param struct
 *
 * Return: this 1 if replaced, 0
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
 * dreplace_string - this function 
 * replaces string
 * @old: this address old string
 * @new: the new string
 *
 * Return: this 1 if replaced, 0
 */
int dreplace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
