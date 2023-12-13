#include "shell.h"

/**
 * dclear_info - initializes info_t struct
 * @info: struct address
 */
void dclear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->dpath = NULL;
	info->argc = 0;
}

/**
 * dset_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void dset_info(info_t *info, char **av)
{
	int di = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = dstrtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _dstrdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (di = 0; info->argv && info->argv[di]; di++)
			;
		info->argc = di;

		dreplace_alias(info);
		dreplace_vars(info);
	}
}

/**
 * dfree_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void dfree_info(info_t *info, int all)
{
	dffree(info->argv);
	info->argv = NULL;
	info->dpath = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			dfree_list(&(info->env));
		if (info->history)
			dfree_list(&(info->history));
		if (info->alias)
			dfree_list(&(info->alias));
		dffree(info->environ);
			info->environ = NULL;
		dbfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_dputchar(BUF_FLUSH);
	}
}
