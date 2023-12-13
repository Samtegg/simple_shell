#include "shell.h"

/**
 **_dstrncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_dstrncpy(char *dest, char *src, int n)
{
	int di, dj;
	char *ds = dest;

	di = 0;
	while (src[di] != '\0' && di < n - 1)
	{
		dest[di] = src[di];
		di++;
	}
	if (di < n)
	{
		dj = di;
		while (dj < n)
		{
			dest[dj] = '\0';
			dj++;
		}
	}
	return (ds);
}

/**
 **_dstrncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_dstrncat(char *dest, char *src, int n)
{
	int di, dj;
	char *ds = dest;

	di = 0;
	dj = 0;
	while (dest[di] != '\0')
		di++;
	while (src[dj] != '\0' && dj < n)
	{
		dest[di] = src[dj];
		di++;
		dj++;
	}
	if (dj < n)
		dest[di] = '\0';
	return (ds);
}

/**
 **_dstrchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_dstrchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
