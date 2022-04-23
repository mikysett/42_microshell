#include "ft_microshell.h"

size_t ft_strlen(char *str)
{
	const char *o_str = str;
	while (*str)
		str++;
	return (str - o_str);
}

char *ft_strdup(char *str)
{
	const size_t str_len = ft_strlen(str);
	char *new_str = ft_calloc(str_len + 1);
	
	size_t i = 0;
	while (i < str_len)
	{
		new_str[i] = str[i];
		i++;
	}
	return (new_str);
}

void ft_putstr_fd(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}


void ft_pushback(t_tkn **tokens, t_tkn *new_tkn)
{
	t_tkn *head = *tokens;

	if (!head)
		*tokens = new_tkn;
	else
	{
		while(head->next)
			head = head->next;
		head->next = new_tkn;
	}
}


void *ft_calloc(size_t size)
{
	void *ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd(2, "error: fatal\n");
		exit(1);
	}

	size_t i = 0;
	while (i < size)
	{
		*(char *)(ptr + i) = 0;
		i++;
	}
	return (ptr);
}

int ft_pipe(int *pipes)
{
	int res = pipe(pipes);
	if (res == -1)
	{
		ft_putstr_fd(2, "error: fatal");
		exit(1);
	}
	return (res);
}

int ft_dup(int fd)
{
	int res = dup(fd);
	if (res == -1)
	{
		ft_putstr_fd(2, "error: fatal");
		exit(1);
	}
	return (res);
}

int ft_dup2(int fd1, int fd2)
{
	int res = dup2(fd1, fd2);
	if (res == -1)
	{
		ft_putstr_fd(2, "error: fatal");
		exit(1);
	}
	return (res);
}


