#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define MAX_ARGS 10

extern char **environ;

char **tokenate(char *str);
char *path_finder(char *file);
void freetok(char **head);
int builtin(char **toks);
void execute(char **toks, char *file);
void env(void);

#endif /* SHELL */
