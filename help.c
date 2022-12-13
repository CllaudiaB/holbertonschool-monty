#include "monty.h"
/**
 * _isdigit - Checks for a digit 0 through 9
 * Return: 0 or 1
 * @c: Variable
 **/
int _isdigit(char *c)
{
	char *temp = c;

	if (c == NULL)
		return (0);
	if (*temp == '-')
		temp++;

	for (; *temp != '\0'; temp++)
	{
		if ((*temp < '0' || *temp > '9'))
		{
			return (0);
		}
	}
	return (1);
}

/**
 * cleanStack - Frees mallocs and close de files
 * @stack: Stack
 */
void cleanStack(stack_t **stack)
{
	stack_t *current = *stack;

	for (; current; current = *stack)
	{
		*stack = (*stack)->next;
		free(current);
	}
	fclose(buffer.fd);
	free(buffer.line);
}
