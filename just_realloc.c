#include "shell.h"

/**
 **_dmemset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_dmemset(char *s, char b, unsigned int n)
{
	unsigned int di;

	for (di = 0; di < n; di++)
		s[di] = b;
	return (s);
}

/**
 * dffree - frees a string of strings
 * @pp: string of strings
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
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
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
