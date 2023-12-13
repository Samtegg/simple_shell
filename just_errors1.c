#include "shell.h"

/**
 * _derratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _derratoi(char *s)
{
	int d = 0;
	unsigned long int dresult = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (d = 0;  s[d] != '\0'; d++)
	{
		if (s[d] >= '0' && s[d] <= '9')
		{
			dresult *= 10;
			dresult += (s[d] - '0');
			if (dresult > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (dresult);
}

/**
 * dprint_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void dprint_error(info_t *info, char *estr)
{
	_deputs(info->fname);
	_deputs(": ");
	dprint_d(info->line_count, STDERR_FILENO);
	_deputs(": ");
	_deputs(info->argv[0]);
	_deputs(": ");
	_deputs(estr);
}

/**
 * dprint_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int dprint_d(int input, int fd)
{
	int (*__dputchar)(char) = _dputchar;
	int d, dcount = 0;
	unsigned int _dabs_, dcurrent;

	if (fd == STDERR_FILENO)
		__dputchar = _deputchar;
	if (input < 0)
	{
		_dabs_ = -input;
		__dputchar('-');
		dcount++;
	}
	else
		_dabs_ = input;
	dcurrent = _dabs_;
	for (d = 1000000000; d > 1; d /= 10)
	{
		if (_dabs_ / d)
		{
			__dputchar('0' + dcurrent / d);
			dcount++;
		}
		dcurrent %= d;
	}
	__dputchar('0' + dcurrent);
	dcount++;

	return (dcount);
}

/**
 * dconvert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *dconvert_number(long int num, int base, int flags)
{
	static char *darray;
	static char buffer[50];
	char dsign = 0;
	char *dptr;
	unsigned long dn = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		dn = -num;
		dsign = '-';

	}
	darray = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	dptr = &buffer[49];
	*dptr = '\0';

	do	{
		*--dptr = darray[dn % base];
		dn /= base;
	} while (dn != 0);

	if (dsign)
		*--dptr = dsign;
	return (dptr);
}

/**
 * dremove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void dremove_comments(char *buf)
{
	int di;

	for (di = 0; buf[di] != '\0'; di++)
		if (buf[di] == '#' && (!di || buf[di - 1] == ' '))
		{
			buf[di] = '\0';
			break;
		}
}
