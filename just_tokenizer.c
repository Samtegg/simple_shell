#include "shell.h"

/**
 * **dstrtow - this function splits a string
 * to words
 * @str: input strg
 * @d: delimeter strg
 * Return: pointer to array of strings.
 */

char **dstrtow(char *str, char *d)
{
	int di, dj, dk, dm, dnumwords = 0;
	char **ds;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (di = 0; str[di] != '\0'; di++)
		if (!dis_delim(str[di], d) && (dis_delim(str[di + 1], d) || !str[di + 1]))
			dnumwords++;

	if (dnumwords == 0)
		return (NULL);
	ds = malloc((1 + dnumwords) * sizeof(char *));
	if (!ds)
		return (NULL);
	for (di = 0, dj = 0; dj < dnumwords; dj++)
	{
		while (dis_delim(str[di], d))
			di++;
		dk = 0;
		while (!dis_delim(str[di + dk], d) && str[di + dk])
			dk++;
		ds[dj] = malloc((dk + 1) * sizeof(char));
		if (!ds[dj])
		{
			for (dk = 0; dk < dj; dk++)
				free(ds[dk]);
			free(ds);
			return (NULL);
		}
		for (dm = 0; dm < dk; dm++)
			ds[dj][dm] = str[di++];
		ds[dj][dm] = 0;
	}
	ds[dj] = NULL;
	return (ds);
}

/**
 * **strtow2 - this function splits
 * string into words
 * @str: input string
 * @d: delimeter
 * Return: the pointer to array strings.
 */
char **dstrtow2(char *str, char d)
{
	int di, dj, dk, dm, dnumwords = 0;
	char **ds;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (di = 0; str[di] != '\0'; di++)
		if ((str[di] != d && str[di + 1] == d) ||
		    (str[di] != d && !str[di + 1]) || str[di + 1] == d)
			dnumwords++;
	if (dnumwords == 0)
		return (NULL);
	ds = malloc((1 + dnumwords) * sizeof(char *));
	if (!ds)
		return (NULL);
	for (di = 0, dj = 0; dj < dnumwords; dj++)
	{
		while (str[di] == d && str[di] != d)
			di++;
		dk = 0;
		while (str[di + dk] != d && str[di + dk] && str[di + dk] != d)
			dk++;
		ds[dj] = malloc((dk + 1) * sizeof(char));
		if (!ds[dj])
		{
			for (dk = 0; dk < dj; dk++)
				free(ds[dk]);
			free(ds);
			return (NULL);
		}
		for (dm = 0; dm < dk; dm++)
			ds[dj][dm] = str[di++];
		ds[dj][dm] = 0;
	}
	ds[dj] = NULL;
	return (ds);
}
