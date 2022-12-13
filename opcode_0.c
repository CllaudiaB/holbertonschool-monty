#include "monty.h"

int value;
/**
 * new_Node - creates a new node
 * @n: data of the new node
 * Return: pointer to new node
 */
stack_t *new_Node(int n)
{
	stack_t *new = NULL;

	new = malloc(sizeof(stack_t));
	if (new == NULL)
	{
		dprintf(STDERR_FILENO, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new->n = n;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/**
 * _push - creates a new node at the beginning of stack
 * @stack: double pointer to the stack
 * @line_number: line number of the command
 */
void _push(stack_t **stack, unsigned int line_number)
{
	stack_t *new = NULL;
	(void)line_number;

	new = new_Node(value);

	new->next = *stack;
	if (*stack != NULL)
		(*stack)->prev = new;
	*stack = new;
}

/**
 * _pall - print all the values of the stack
 * @stack: double pointer to the stack
 * @n: data to print
 * Return: nothing
 */

void _pall(stack_t **stack, unsigned int n)
{
	stack_t *current = NULL;
	(void)n;

	current = *stack;

	while (current != NULL)
	{
		dprintf(STDOUT_FILENO, "%d\n", current->n);
		current = current->next;
	}
}

/**
 * _pint - prints the value at the top of the stack
 * @stack: doubly linked list storing the data
 * @n: line of the command
 */

void _pint(stack_t **stack, unsigned int n)
{
	stack_t *current = NULL;

	current = *stack;
	if (current == NULL)
	{
		dprintf(STDERR_FILENO, "L%u: can't pint, stack empty", n);
		exit(EXIT_FAILURE);
	}

	dprintf(STDOUT_FILENO, "%d\n", current->n);
}
