#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _dmyexit(info_t *info)
{
	int dexitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		dexitcheck = _derratoi(info->argv[1]);
		if (dexitcheck == -1)
		{
			info->status = 2;
			dprint_error(info, "Illegal number: ");
			_deputs(info->argv[1]);
			_deputchar('\n');
			return (1);
		}
		info->err_num = _derratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _dmycd(info_t *info)
{
	char *d, *ddir, buffer[1024];
	int dchdir_ret;

	d = getcwd(buffer, 1024);
	if (!d)
		_dputs("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		ddir = _dgetenv(info, "HOME=");
		if (!ddir)
			dchdir_ret = /* TODO: what should this be? */
				chdir((ddir = _dgetenv(info, "PWD=")) ? ddir : "/");
		else
			dchdir_ret = chdir(ddir);
	}
	else if (_dstrcmp(info->argv[1], "-") == 0)
	{
		if (!_dgetenv(info, "OLDPWD="))
		{
			_dputs(d);
			_dputchar('\n');
			return (1);
		}
		_dputs(_dgetenv(info, "OLDPWD=")), _dputchar('\n');
		dchdir_ret = /* TODO: what then should this be? */
			chdir((ddir = _dgetenv(info, "OLDPWD=")) ? ddir : "/");
	}
	else
		dchdir_ret = chdir(info->argv[1]);
	if (dchdir_ret == -1)
	{
		dprint_error(info, "can't cd to ");
		_deputs(info->argv[1]), _dputchar('\n');
	}
	else
	{
		_dsetenv(info, "OLDPWD", _dgetenv(info, "PWD="));
		_dsetenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _dmyhelp(info_t *info)
{
	char **darg_array;

	darg_array = info->argv;
	_dputs("help call works. Function not yet implemented \n");
	if (0)
		_dputs(*darg_array); /* temp att_unused workaround */
	return (0);
}
