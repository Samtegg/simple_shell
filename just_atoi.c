#include "shell.h"

/**
 * dinteractive - this function returns true 
 * if shell is interactive mode
 * @info: the struct address
 *
 * Return: this will return 1 if interactive mode, 0 otherwise
 */
int dinteractive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * dis_delim - this function checks if character is a delimeter
 * @c: this is the char to check
 * @delim: this is the delimeter string
 * Return: this will return 1 if true, 0 if false
 */
int dis_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_disalpha - this function checks 
 alphabetic character
 *@c: this is the char to input
 *Return: this will return 1 if c is alphabetic, 0 otherwise
 */

int _disalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_datoi - this is the function that 
 converts a string to an integer
 *@s: this is the string to be converted
 *Return: this will return 0 if no numbers in string,
 converted number otherwise
 */

int _datoi(char *s)
{
	int d, dsign = 1, dflag = 0, doutput;
	unsigned int dresult = 0;

	for (d = 0;  s[d] != '\0' && dflag != 2; d++)
	{
		if (s[d] == '-')
			dsign *= -1;

		if (s[d] >= '0' && s[d] <= '9')
		{
			dflag = 1;
			dresult *= 10;
			dresult += (s[d] - '0');
		}
		else if (dflag == 1)
			dflag = 2;
	}

	if (dsign == -1)
		doutput = -dresult;
	else
		doutput = dresult;

	return (doutput);
}
