#include "shell.h"

/**
 * _dstrcpy - this function
 * copies a string
 * @dest: this is the destination
 * @src: this is the source
 *
 * Return: this is the pointer to destination
 */
char *_dstrcpy(char *dest, char *src)
{
	int di = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[di])
	{
		dest[di] = src[di];
		di++;
	}
	dest[di] = 0;
	return (dest);
}

/**
 * _dstrdup - this function
 * duplicates a string
 * @str: string to duplicate
 *
 * Return: the pointer duplicated string
 */
char *_dstrdup(const char *str)
{
	int dlength = 0;
	char *dret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		dlength++;
	dret = malloc(sizeof(char) * (dlength + 1));
	if (!dret)
		return (NULL);
	for (dlength++; dlength--;)
		dret[dlength] = *--str;
	return (dret);
}

/**
 *_dputs - this function
 prints input string
 *@str: string to print
 *
 * Return: Nothing null
 */
void _dputs(char *str)
{
	int di = 0;

	if (!str)
		return;
	while (str[di] != '\0')
	{
		_dputchar(str[di]);
		di++;
	}
}

/**
 * _dputchar - this function
 * writes charact c to stdout
 * @c: charact to print
 *
 * Return: this returns On success 1.
 * error, -1 is returned, errno set appropriately.
 */
int _dputchar(char c)
{
	static int di;
	static char dbuf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || di >= WRITE_BUF_SIZE)
	{
		write(1, dbuf, di);
		di = 0;
	}
	if (c != BUF_FLUSH)
		dbuf[di++] = c;
	return (1);
}
