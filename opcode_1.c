#include "monty.h"

/**
 * _swap - swaps the top two elements of the stack
 * @stack: doubly linked list storing the data
 * @line_number: line of the command
 * Return: void
 */

void _swap(stack_t **stack, unsigned int line_number)
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
		dprintf(STDERR_FILENO, "L%u: can't swap, stack too short\n", line_number);
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

/**
 *_add - adds the top two elements of the stack
 *@stack: stack storing data
 *@line_number: line of the command
 *
 *Return: nothing
 */

void _add(stack_t **stack, unsigned int line_number)
{
	int i = 0, sum = 0;
	stack_t *temp;

	temp = *stack;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	if (i < 2)
	{
		dprintf(STDERR_FILENO, "L%u: can't add, stack too short\n", line_number);
		fclose(buffer.fd);
		free(buffer.line);
		free(temp);
		exit(EXIT_FAILURE);
	}
	temp = *stack;
	sum = temp->n + temp->next->n;
	temp->next->n = sum;
	_pop(stack, line_number);
}

/**
 * _nop - does not do anything
 * @stack: stack storing data
 * @line_number: line of the command
 * Return: void
 */

void _nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
