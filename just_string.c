#include "shell.h"

/**
 * _dstrlen - this functon
 * will return the len of a string
 * @s: string len to check
 *
 * Return: int length of string
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
 * _dstrcmp - this function performs
 * lexicogarphic comparison both strangs.
 * @s1: first string
 * @s2: second string
 *
 *
 * Return: if s1 < s2, positive if s1 > s2, zero if s1 == s2
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
 * dstarts_with - this function checks
 * if needle starts with haystack
 * @haystack: string search
 * @needle: sub-string find
 *
 * Return: the address next char of haystack or nothing
 */
char *dstarts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _dstrcat - this function concatenates
 * both strings
 * @dest: dest buffer
 * @src: source buf
 *
 * Return: the pointer destination buffer
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
