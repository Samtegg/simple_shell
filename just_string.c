#include "shell.h"

/**
 * _dstrlen - this functon will return len of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _dstrlen(char *s)
{
	int d = 0;

	if (!s)
		return (0);

	while (*s++)
		d++;
	return (d);
}

/**
 * _dstrcmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _dstrcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *dstarts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _dstrcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_dstrcat(char *dest, char *src)
{
	char *dret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (dret);
}
