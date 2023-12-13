#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t d = 0;
	int dbuiltin_ret = 0;

	while (d != -1 && dbuiltin_ret != -2)
	{
		dclear_info(info);
		if (dinteractive(info))
			_dputs("$ ");
		_deputchar(BUF_FLUSH);
		d = dget_input(info);
		if (d != -1)
		{
			dset_info(info, av);
			dbuiltin_ret = dfind_builtin(info);
			if (dbuiltin_ret == -1)
				dfind_cmd(info);
		}
		else if (dinteractive(info))
			_dputchar('\n');
		dfree_info(info, 0);
	}
	dwrite_history(info);
	dfree_info(info, 1);
	if (!dinteractive(info) && info->status)
		exit(info->status);
	if (dbuiltin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (dbuiltin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int dfind_builtin(info_t *info)
{
	int d, dbuilt_in_ret = -1;
	dbuiltin_table dbuiltintbl[] = {
		{"exit", _dmyexit},
		{"env", _dmyenv},
		{"help", _dmyhelp},
		{"history", _dmyhistory},
		{"setenv", _dmysetenv},
		{"unsetenv", _dmyunsetenv},
		{"cd", _dmycd},
		{"alias", _dmyalias},
		{NULL, NULL}
	};

	for (d = 0; dbuiltintbl[d].type; d++)
		if (_dstrcmp(info->argv[0], dbuiltintbl[d].type) == 0)
		{
			info->line_count++;
			dbuilt_in_ret = dbuiltintbl[d].func(info);
			break;
		}
	return (dbuilt_in_ret);
}

/**
 * dfind_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void dfind_cmd(info_t *info)
{
	char *dpath = NULL;
	int d, e;

	info->dpath = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (d = 0, e = 0; info->arg[d]; d++)
		if (!dis_delim(info->arg[d], " \t\n"))
			e++;
	if (!e)
		return;

	dpath = dfind_path(info, _dgetenv(info, "PATH="), info->argv[0]);
	if (dpath)
	{
		info->dpath = dpath;
		dfork_cmd(info);
	}
	else
	{
		if ((dinteractive(info) || _dgetenv(info, "PATH=")
			|| info->argv[0][0] == '/') && dis_cmd(info, info->argv[0]))
			dfork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			dprint_error(info, "not found\n");
		}
	}
}

/**
 * dfork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void dfork_cmd(info_t *info)
{
	pid_t dchild_pid;

	dchild_pid = fork();
	if (dchild_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (dchild_pid == 0)
	{
		if (execve(info->dpath, info->argv, dget_environ(info)) == -1)
		{
			dfree_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				dprint_error(info, "Permission denied\n");
		}
	}
}
