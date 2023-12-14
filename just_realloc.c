#include "shell.h"

/**
 **_dmemset - this function fills
 memory a constant byte
 *@s: pointer to memory area
 *@b: byte fill *s with
 *@n: amount bytes to be filled
 *Return: s pointer to memory area s
 */
char *_dmemset(char *s, char b, unsigned int n)
{
	unsigned int di;

	for (di = 0; di < n; di++)
		s[di] = b;
	return (s);
}

/**
 * dffree - this function frees
 * a string of strings
 * @pp: strings
 */
void dffree(char **pp)
{
	char **da = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(da);
}

/**
 * _drealloc - this function
 * reallocates block of memory
 * @ptr: previous the malloc'ated block
 * @old_size: byte previous block
 * @new_size: byte new block
 *
 * Return: the pointer da ol'block nameen.
 */
void *_drealloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *dp;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	dp = malloc(new_size);
	if (!dp)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		dp[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (dp);
}
