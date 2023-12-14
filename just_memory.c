#include "shell.h"

/**
 * dbfree - this function frees 
 * pointer and NULLs the address
 * @ptr: the address 
 * pointer to free
 *
 * Return: 1, otherwise 0.
 */
int dbfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
