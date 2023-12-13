#include "shell.h"

/**
 * dlist_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t dlist_len(const list_t *h)
{
	size_t di = 0;

	while (h)
	{
		h = h->next;
		di++;
	}
	return (di);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **dlist_to_strings(list_t *head)
{
	list_t *node = head;
	size_t di = dlist_len(head), dj;
	char **dstrs;
	char *str;

	if (!head || !di)
		return (NULL);
	dstrs = malloc(sizeof(char *) * (di + 1));
	if (!dstrs)
		return (NULL);
	for (di = 0; node; node = node->next, di++)
	{
		str = malloc(_dstrlen(node->str) + 1);
		if (!str)
		{
			for (dj = 0; dj < di; dj++)
				free(dstrs[dj]);
			free(dstrs);
			return (NULL);
		}

		str = _dstrcpy(str, node->str);
		dstrs[di] = str;
	}
	dstrs[di] = NULL;
	return (dstrs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t dprint_list(const list_t *h)
{
	size_t di = 0;

	while (h)
	{
		_dputs(dconvert_number(h->num, 10, 0));
		_dputchar(':');
		_dputchar(' ');
		_dputs(h->str ? h->str : "(nil)");
		_dputs("\n");
		h = h->next;
		di++;
	}
	return (di);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *dnode_starts_with(list_t *node, char *prefix, char c)
{
	char *dp = NULL;

	while (node)
	{
		dp = dstarts_with(node->str, prefix);
		if (dp && ((c == -1) || (*dp == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t dget_node_index(list_t *head, list_t *node)
{
	size_t di = 0;

	while (head)
	{
		if (head == node)
			return (di);
		head = head->next;
		di++;
	}
	return (-1);
}
