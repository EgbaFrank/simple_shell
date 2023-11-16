#include "shell.h"

/**
 * path_finder - checks if a file is present in current PATH
 * @file: file to be checked
 *
 * Return: absolute path to file
 */

char *path_finder(char *file)
{
	const char *path;
	char *copy = NULL, *filepath = NULL, *fullpath = NULL;

		path = getenv("PATH");
		if (path == NULL)
		{
			/* fprintf(stderr, "PATH variable not set\n"); */
			return (NULL);
		}
		copy = strdup(path);
		filepath = strtok(copy, ":");
		fullpath = malloc(strlen(filepath) + strlen(file) + 3);
		if (fullpath == NULL)
		{
			perror("Path");
			return (NULL);
		}
		while (filepath != NULL)
		{
			strcpy(fullpath, filepath);
			strcat(fullpath, "/");
			strcat(fullpath, file);
			if (access(fullpath, F_OK) == 0)
			{
				free(copy);
				return (fullpath);
			}
			filepath = strtok(NULL, ":");
		}
		free(fullpath);
		free(copy);

	return (NULL);
}
