#include "shell.h"

/**
 * dis_cmd - this function determines
 * if a file executable command
 * @info: the info struct
 * @path: the path to file
 *
 * Return: 1, 0 otherwise
 */
int dis_cmd(info_t *info, char *path)
{
	struct stat dst;

	(void)info;
	if (!path || stat(path, &dst))
		return (0);

	if (dst.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - this function
 * duplicate charact
 * @pathstr: path string
 * @start: the start index
 * @stop: last stop index
 *
 * Return: the pointer new buffer
 */
char *ddup_chars(char *pathstr, int start, int stop)
{
	static char dbuf[1024];
	int di = 0, dk = 0;

	for (dk = 0, di = start; di < stop; di++)
		if (pathstr[di] != ':')
			dbuf[dk++] = pathstr[di];
	dbuf[dk] = 0;
	return (dbuf);
}

/**
 * dfind_path - this function finds
 * this cmd in the PATH string
 * @info: info struct
 * @pathstr: path string
 * @cmd: cmd to find
 *
 * Return: path cmd if found or NULL
 */
char *dfind_path(info_t *info, char *pathstr, char *cmd)
{
	int di = 0, dcurr_pos = 0;
	char *dpath;

	if (!pathstr)
		return (NULL);
	if ((_dstrlen(cmd) > 2) && dstarts_with(cmd, "./"))
	{
		if (dis_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[di] || pathstr[di] == ':')
		{
			dpath = ddup_chars(pathstr, dcurr_pos, di);
			if (!*dpath)
				_dstrcat(dpath, cmd);
			else
			{
				_dstrcat(dpath, "/");
				_dstrcat(dpath, cmd);
			}
			if (dis_cmd(info, dpath))
				return (dpath);
			if (!pathstr[di])
				break;
			dcurr_pos = di;
		}
		di++;
	}
	return (NULL);
}
