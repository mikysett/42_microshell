#ifndef FT_MICROSHELL_H
# define FT_MICROSHELL_H

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

typedef enum s_tkn_type
{
	WORD,
	OP_PIPE,
	OP_STOP
} t_tkn_type;

typedef struct s_tkn
{
	t_tkn_type type;
	char *str;
	struct s_tkn *next;
} t_tkn;

typedef struct s_cmd
{
	char *path;
	char **args;
	bool redir_in;
	bool redir_out;
} t_cmd;

// test.c
void print_cmd(t_cmd *cmd);

// util.c
size_t ft_strlen(char *str);
char *ft_strdup(char *str);
void ft_putstr_fd(int fd, char *str);

void ft_pushback(t_tkn **tokens, t_tkn *new_tkn);

void *ft_calloc(size_t size);
int ft_pipe(int *pipes);
int ft_dup(int fd);
int ft_dup2(int fd1, int fd2);

// parser.c
void parser(t_tkn **tokens, int argc, char **argv);

// executor.c
void executor(t_tkn *head, char **envp);

// redir.c
void redir(t_cmd *cmd, int stdin_copy, int stdout_copy);

#endif