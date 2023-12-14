#include "shell.h"

/**
 * dlist_len - this function determines
 * length linked list
 * @h: first node
 *
 * Return: the size list
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
 * dlist_to_strings - this function returns
 * array of strings list->str
 * @head: the pointer first node
 *
 * Return: the array strings
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
 * dprint_list - this function prints
 * all elements list_t linked list
 * @h: the pointer to first node
 *
 * Return: the size list
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
 * dnode_starts_with - this function returns
 * node whose string starts with prefix
 * @node: the pointer
 * list head
 * @prefix: the string
 * to match
 * @c: next character prefix to match
 *
 * Return: the node or null
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
 * dget_node_index - this function gets
 * the index of a node
 * @head: the pointer list head
 * @node: the pointer the node
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
