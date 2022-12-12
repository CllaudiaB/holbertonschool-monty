#include "monty.h"

buffer_t buffer = {NULL, NULL};
/**
 * main - Entry point
 * @argc: Number of arguments
 * @argv: pointers to arguments
 * Return: 0
 */
int main(int argc, char *argv[])
{
	if (argc == 2)
		execute_cmd(argv[1]);
	else
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
/**
 * execute_cmd - executes user input
 * @argv: user input to execute
 * Return: void
 */
void execute_cmd(char *argv)
{
	int count = 0, result = 0;
	size_t bufsize = 0;
	char *arguments = NULL, *item = NULL;
	stack_t *stack = NULL;

	buffer.fd = fopen(argv, "r");
	if (buffer.fd)
	{
		while (getline(&buffer.line, &bufsize, buffer.fd) != -1)
		{
			count++;
			arguments = strtok(buffer.line, " \n\t\r");
			if (arguments == NULL)
			{
				free(arguments);
				continue;
			}
			else if (*arguments == '#')
				continue;
			item = strtok(NULL, " \n\t\r");
			result = get_opc(&stack, arguments, item, count);
/*			if (result == 1)
				push_error(global.fd, global.line, stack, count);
			else if (result == 2)
			ins_error(global.fd, global.line, stack, arguments, count);*/
		}
		free(buffer.line);
		free_dlistint(stack);
		fclose(buffer.fd);
	}
	else
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", argv);
		exit(EXIT_FAILURE);
	}
}
/**
 * get_opc - function to handle the opcode
 * @stack: is a stack or queue
 * @arg: is a parameter
 * @item: is a parameter
 * @count: is a line command
 * Return: nothing
 */
int get_opc(stack_t **stack, char *arg, char *item, int count)
{
	int i = 0;

	instruction_t op[] = {
		{"push", _push},
		{"pall", _pall},
		{NULL, NULL}
	};

	while (op[i].opcode)
	{
		if (!strcmp(arg, op[i].opcode))
		{
			if (!strcmp(arg, "push"))
			{
				if (_isdigit(item) == 1)
					value = atoi(item);
				else
					return (1);
			}
			op[i].f(stack, (unsigned int)count);
			break;
		}
		i++;
	}
	if (!op[i].opcode)
		return (2);

	return (0);
}
