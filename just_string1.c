#include "shell.h"

/**
 * _dstrcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
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
 * _dstrdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
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
 *_dputs - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
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
 * _dputchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
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
