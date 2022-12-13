#include "monty.h"

/**
 * _swap - swaps the top two elements of the stack
 * @stack: doubly linked list storing the data
 * @n: line of the command
 */

void _swap(stack_t **stack, unsigned int n)
{
	stack_t *temp = *stack, *head = *stack;
	int i = 0, tempdata, headdata;

	while (temp)
	{
		temp = temp->next;
		i++;
	}
	if (i < 2)
	{
		dprintf(STDERR_FILENO, "L%u: can't swap, stack too short\n", n);
		fclose(buffer.fd);
		free(buffer.line);
		free(temp);
		free(head);
		exit(EXIT_FAILURE);
	}
	temp = *stack;
	headdata = head->n;
	temp = temp->next;
	tempdata = temp->n;
	temp->n = headdata;
	head->n = tempdata;
}
