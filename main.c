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
	if (argc == 2)
	{
		handle_command(argv[1]);
	}
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

void handle_command(char *argv)
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
			fprintf(stderr, "getline return value is %ld\n", getline(&buffer.line, &bufsize, buffer.fd));
                        fprintf(stderr, "debut de boucle while : buffer : %s\n", buffer.line);
			count++;
			arguments = strtok(buffer.line, " \n\t\r");
			fprintf(stderr, "argument is %s\n", arguments);
			if (arguments == NULL)
			{
				free(arguments);
				continue;
			}
			else if (*arguments == '#')
			continue;
			item = strtok(NULL, " \n\t\r");
			fprintf(stderr, "data is %s\n", item);
			result = opc_function(&stack, arguments, item, count);
/*			if (result == 1)
				push_error(buffer.fd, buffer.line, stack, count);
			else if (result == 2)
			ins_error(global.fd, buffer.line, stack, arguments, count);*/
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

/*void execute_cmd(char *argv)
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
			fprintf(stderr, "getline return value is %ld\n", getline(&buffer.line, &bufsize, buffer.fd));
			fprintf(stderr, "debut de boucle while : buffer : %s\n", buffer.line);
			linecount++;
			arguments = strtok(buffer.line, " \n");
			fprintf(stderr, "linecount is %u, and arguments is %s\n", linecount, arguments);
			if (arguments == NULL)
			{
				free(arguments);
				continue;
			}
			data = strtok(NULL, " \n");
			printf("in execute cmd, data is : %s\n", data);
			result = opc_function(&stack, arguments, data, linecount);
			fprintf(stderr, "just executed opc_func in execute cmd\n");
 			fprintf(stderr, "result is : %d\n", result);
			if (result == 1)
			{
				dprintf(STDERR_FILENO, "L%u: usage: push integer\n", linecount);
				fclose(buffer.fd);
				free(buffer.line);
				free_dlistint(stack);
				exit(EXIT_FAILURE);
				}*/
/*			free(buffer.line);*/
/*			free_dlistint(stack);*/
/*			fclose(buffer.fd);*/
/*		}
		free(buffer.line);
		free_dlistint(stack);
		fclose(buffer.fd);

	}
	}*/

/**
 * opc_function - checks if the user input is a valid command
 * @stack: double pointer to the stack
 * @argument: the command entered by the user
 * @data: data entered by the user
 * @linecount: number of lines entered
 * Return: 0 if the command does not exist, 1 if push not followed by digit
 * 2 if success
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

	while (op[i].opcode)
	{
		fprintf(stderr, "entered opc_function, i = %d\n", i);
		if (!strcmp(argument, op[i].opcode))
		{
			if (!strcmp(argument, "push"))
			{
				fprintf(stderr, "entered strcmp to check if data isdigit\n");
				if (isdigit(data) == 1)
					value = atoi(data);
				else
					return (1);
			}
			op[i].f(stack, (unsigned int)linecount);
			break;
		}
		i++;
	}
	if (!op[i].opcode)
		return (2);
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
