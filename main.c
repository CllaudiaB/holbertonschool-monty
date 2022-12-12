#include "monty.h"

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
