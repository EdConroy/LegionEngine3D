#include <stdlib.h>
#include "legion_lib.h"

void legion_print_list(node * head) 
{
	node * current = head;
	while (current != NULL) 
	{
		printf("%d\n", current->val);
		current = current->next;
	}
}

void legion_push_to_end(node* head, int val) 
{
	node* current = head;

	while (current->next != NULL) 
		current = current->next;
	
	current->next = malloc(sizeof(node));
	current->next->val = val;
	current->next->next = NULL;
}

void legion_push_to_front(node** head, int val)
{
	node* new_node;
	new_node = malloc(sizeof(node));

	new_node->val = val;
	new_node->next = head;
	*head = new_node;
}

int legion_pop(node** head)
{
	int retVal = -1;

	node* next_node = NULL;
	
	if (*head == NULL)
	{
		return -1;
	}
	next_node = (*head)->next;
	retVal = (*head)->val;
	free(*head);
	*head = next_node;

	return retVal;
}
int legion_remove_last(node* head)
{
	int retVal = 0;

	if (head->next == NULL)
	{
		head->val = 0;
		free(head);
		head = NULL;
		return retVal;
	}

	node* current = head;
	
	while (current->next->next != NULL)
		current = current->next;
}
int legion_remove_by_index(node** head, int n)
{
	int i = 0;
	int retVal = -1;
	node* current = *head;
	node* temp_node = NULL;

	if (n == 0)
	{
		return legion_pop(head);
	}

	for (i = 0; i < n - 1; i++)
	{
		if (current->next == NULL)
		{
			return -1;
		}
		current = current->next;
	}

	temp_node = current->next;
	retVal = temp_node->val;
	current->next = temp_node->next;
	free(temp_node);
	return retVal;
}
int legion_remove_by_value(node* list, void* val)
{
	int retVal = -1;
	node* current = list->head;
	node* temp_node = NULL;

	for (node *ptr = list->head; ptr; ptr = ptr->next)
	{
		if (ptr == val)
		{
			temp_node = current->next;
			retVal = temp_node->val;
			current->next = temp_node->next;
			free(temp_node);
			return retVal;
		}
	}
	return -1;
}