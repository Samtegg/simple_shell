#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *dget_history_file(info_t *info)
{
	char *dbuf, *ddir;

	ddir = _dgetenv(info, "HOME=");
	if (!ddir)
		return (NULL);
	dbuf = malloc(sizeof(char) * (_dstrlen(ddir) + _dstrlen(HIST_FILE) + 2));
	if (!dbuf)
		return (NULL);
	dbuf[0] = 0;
	_dstrcpy(dbuf, ddir);
	_dstrcat(dbuf, "/");
	_dstrcat(dbuf, HIST_FILE);
	return (dbuf);
}

/**
 * dwrite_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int dwrite_history(info_t *info)
{
	ssize_t dfd;
	char *dfilename = dget_history_file(info);
	list_t *dnode = NULL;

	if (!dfilename)
		return (-1);

	dfd = open(dfilename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(dfilename);
	if (dfd == -1)
		return (-1);
	for (dnode = info->history; dnode; dnode = dnode->next)
	{
		_dputsfd(dnode->str, dfd);
		_dputfd('\n', dfd);
	}
	_dputfd(BUF_FLUSH, dfd);
	close(dfd);
	return (1);
}

/**
 * dread_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int dread_history(info_t *info)
{
	int di, dlast = 0, dlinecount = 0;
	ssize_t dfd, drdlen, dfsize = 0;
	struct stat dst;
	char *dbuf = NULL, *dfilename = dget_history_file(info);

	if (!dfilename)
		return (0);

	dfd = open(dfilename, O_RDONLY);
	free(dfilename);
	if (dfd == -1)
		return (0);
	if (!fstat(dfd, &dst))
		dfsize = dst.st_size;
	if (dfsize < 2)
		return (0);
	dbuf = malloc(sizeof(char) * (dfsize + 1));
	if (!dbuf)
		return (0);
	drdlen = read(dfd, dbuf, dfsize);
	dbuf[dfsize] = 0;
	if (drdlen <= 0)
		return (free(dbuf), 0);
	close(dfd);
	for (di = 0; di < dfsize; di++)
		if (dbuf[di] == '\n')
		{
			dbuf[di] = 0;
			dbuild_history_list(info, dbuf + dlast, dlinecount++);
			dlast = di + 1;
		}
	if (dlast != di)
		dbuild_history_list(info, dbuf + dlast, dlinecount++);
	free(dbuf);
	info->histcount = dlinecount;
	while (info->histcount-- >= HIST_MAX)
		ddelete_node_at_index(&(info->history), 0);
	drenumber_history(info);
	return (info->histcount);
}

/**
 * dbuild_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int dbuild_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	dadd_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int drenumber_history(info_t *info)
{
	list_t *dnode = info->history;
	int di = 0;

	while (dnode)
	{
		dnode->num = di++;
		dnode = dnode->next;
	}
	return (info->histcount = di);
}
