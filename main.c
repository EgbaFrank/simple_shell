#include "shell.h"

/**
 * main - learning about the shell
 * @ac: argument counter
 * @av: argument vector
 *
 * Return: always return 0
 */

int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t nread;
	char **token;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 5);

		nread = getline(&lineptr, &n, stdin);

		if (nread == -1)
			break;

		lineptr[nread - 1] = '\0';
		token = tokenate(lineptr);

		if (token[0] != NULL)
		{
			if (builtin(token, lineptr) == 1)
			{
				env();
				freetok(token);
				continue;
			}
			else
				execute(token, av[0]);
		}
		freetok(token);
	}
	free(lineptr);
	return (0);
}

/**
 * execute - checks for command and execute
 * @toks: an array of strings of commands
 * @file: name of file
 *
 * Return: void
 */

void execute(char **toks, char *file)
{
	char *filename = strdup(toks[0]), *fullpath = NULL;
	pid_t pid;
	int status;

	if (filename == NULL)
	{
		perror("Execution memory allocation failed");
		return;
	}
	fullpath = path_finder(filename);
	if (toks[0][0] == '/' || toks[0][0] == '.')
	{}
	else if (fullpath != NULL)
	{
		free(toks[0]);
		toks[0] = fullpath;
	}
	else
	{
		fprintf(stderr, "%s: 1: %s: not found\n", file, filename);
		free(filename);
		return;
	}
	pid = fork();
	if (pid == -1)
	{
		perror(filename);
		free(filename);
	}
	if (pid == 0)
	{
		if (execve(toks[0], toks, environ) == -1)
		{
			perror(filename);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	wait(&status);
	free(filename);
}

/**
 * freetok - frees an array of strings
 * @head: an array of strings
 *
 * Return: void
 */

void freetok(char **head)
{
	int i;

	for (i = 0; head[i] != NULL; ++i)
	{
		free(head[i]);
	}
	free(head);
}

/**
 * builtin - handles builtin commands exit and env
 * @toks: array of strings
 * @line: a string to be freed
 *
 * Return: void
 */

int builtin(char **toks, char *line)
{
	int status = 0;

	if (strcmp(toks[0], "env") == 0)
		return (1);

	else if (strcmp(toks[0], "exit") == 0)
	{
		freetok(toks);
		free(line);

		exit(status);
	}

	else
		return (0);
}

/**
 * env - prints environment variables
 *
 * Return: void
 */

void env(void)
{
	int i;

	for (i = 0; environ[i] != NULL; ++i)
		printf("%s\n", environ[i]);
}
