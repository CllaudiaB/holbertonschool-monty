#include "monty.h"

buffer_t buffer = {NULL, NULL};

/**
 * main - entry point
 * @argc: number of arguments
 * @argv: pointers to each arguments
 * Return: 0
 */

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	else
		execute_cmd(argv[1]);
	return (0);
}

/**
 * execute_cmd - executes user input
 * @argv: user input to execute
 * Return: void
 */

void execute_cmd(char *argv)
{
	size_t bufsize = 0;
	int result = 0;
	unsigned int linecount = 0;
	char *arguments = NULL, *data = NULL;
	stack_t *stack = NULL;

	buffer.fd = fopen(argv, "r");
	if (buffer.fd == NULL)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", argv);
		exit(EXIT_FAILURE);
	}
	else
	{
		while (getline(&buffer.line, &bufsize, buffer.fd) != -1)
		{
			linecount++;
			arguments = strtok(buffer.line, " \n");
			if (arguments == NULL)
			{
				free(arguments);
				continue;
			}
			data = strtok(NULL, " \n");
			result = opc_function(&stack, arguments, data, linecount);
			if (result == 1)
			{
				dprintf(STDERR_FILENO, "L%u: usage: push integer\n", linecount);
				fclose(buffer.fd);
				free(buffer.line);
				free_dlistint(stack);
				exit(EXIT_FAILURE);
			}
			free(buffer.line);
			free_dlistint(stack);
			fclose(buffer.fd);
		}

	}
}

/**
 * opc_function - checks if the user input is a valid command
 * @stack: double pointer to the stack
 * @argument: the command entered by the user
 * @data: data entered by the user
 * @linecount: number of lines entered
 * Return: 0 if the command does not exist, 1 if push not followed by digit
 */

int opc_function(stack_t **stack, char *argument, char *data, unsigned int linecount)
{
	int i = 0;

	instruction_t op[] = {
		{"push", _push},
		{"pall", _pall},
/*		{"pint", _pint},
		{"pop", _pop},
		{"swap", _swap},
		{"add", _add},
		{"nop", _nop},*/
		{NULL, NULL}
	};

	while (op[i].opcode != NULL)
	{
		if (strcmp(argument, op[i].opcode) == 0)
		{
			if (strcmp(argument, "push"))
			{
				if (isdigit(data))
					value = atoi(data);
				else
					return (1);
			}
			op[i].f(stack, linecount);
		}
		i++;
	}
	return (0);
}

/**
 * freedoublep - frees a double pointer
 * Description: frees a double pointer
 * @p: double pointer to free
 * Return: void
 */

void free_dlistint(stack_t *head)
{
	stack_t *temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
	free(head);
}
