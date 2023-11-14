#include "shell.h"

/**
 * tokenate - splits a space seperated string into tokens
 * @str: string to be tokenized
 *
 * Return: an array of words from string
 */

char **tokenate(char *str)
{
	char **tokens = NULL;
	char *copy = strdup(str);
	char *token = strtok(copy, " ");
	size_t tok_id = 0;

	while (token != NULL)
	{
		tokens = realloc(tokens, (tok_id + 1) * sizeof(char *));
		if (tokens == NULL)
		{
			perror("Memory allocation failed");
			free(copy);
			exit(EXIT_FAILURE);
		}

		tokens[tok_id] = strdup(token);
		tok_id++;

		token = strtok(NULL, " ");
	}

	tokens = realloc(tokens, (tok_id + 1) * sizeof(char *));
	if (tokens == NULL)
	{
		perror("Memory allocation failed");
		free(copy);
		exit(EXIT_FAILURE);
	}
	tokens[tok_id] = NULL;

	free(copy);
	return (tokens);
}
