#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *dadd_node(list_t **head, const char *str, int num)
{
	list_t *dnew_head;

	if (!head)
		return (NULL);
	dnew_head = malloc(sizeof(list_t));
	if (!dnew_head)
		return (NULL);
	_dmemset((void *)dnew_head, 0, sizeof(list_t));
	dnew_head->num = num;
	if (str)
	{
		dnew_head->str = _dstrdup(str);
		if (!dnew_head->str)
		{
			free(dnew_head);
			return (NULL);
		}
	}
	dnew_head->next = *head;
	*head = dnew_head;
	return (dnew_head);
}

/**
 * dadd_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *dadd_node_end(list_t **head, const char *str, int num)
{
	list_t *dnew_node, *dnode;

	if (!head)
		return (NULL);

	dnode = *head;
	dnew_node = malloc(sizeof(list_t));
	if (!dnew_node)
		return (NULL);
	_dmemset((void *)dnew_node, 0, sizeof(list_t));
	dnew_node->num = num;
	if (str)
	{
		dnew_node->str = _dstrdup(str);
		if (!dnew_node->str)
		{
			free(dnew_node);
			return (NULL);
		}
	}
	if (dnode)
	{
		while (dnode->next)
			dnode = dnode->next;
		dnode->next = dnew_node;
	}
	else
		*head = dnew_node;
	return (dnew_node);
}

/**
 * dprint_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t dprint_list_str(const list_t *h)
{
	size_t di = 0;

	while (h)
	{
		_dputs(h->str ? h->str : "(nil)");
		_dputs("\n");
		h = h->next;
		di++;
	}
	return (di);
}

/**
 * ddelete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int ddelete_node_at_index(list_t **head, unsigned int index)
{
	list_t *dnode, *dprev_node;
	unsigned int di = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		dnode = *head;
		*head = (*head)->next;
		free(dnode->str);
		free(dnode);
		return (1);
	}
	dnode = *head;
	while (dnode)
	{
		if (di == index)
		{
			dprev_node->next = dnode->next;
			free(dnode->str);
			free(dnode);
			return (1);
		}
		di++;
		dprev_node = dnode;
		dnode = dnode->next;
	}
	return (0);
}

/**
 * dfree_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void dfree_list(list_t **head_ptr)
{
	list_t *dnode, *dnext_node, *dhead;

	if (!head_ptr || !*head_ptr)
		return;
	dhead = *head_ptr;
	dnode = dhead;
	while (dnode)
	{
		dnext_node = dnode->next;
		free(dnode->str);
		free(dnode);
		dnode = dnext_node;
	}
	*head_ptr = NULL;
}
