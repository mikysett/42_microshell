#include "ft_microshell.h"

char **ft_set_args(t_tkn *head)
{
	int nb_args = 0;
	t_tkn *o_head = head;

	while (head && head->type == WORD)
	{
		head = head->next;
		nb_args++;
	}

	char **args = ft_calloc(sizeof(char *) * (nb_args + 1));
	int i = 0;
	head = o_head;
	while (i < nb_args)
	{
		args[i] = ft_strdup(head->str);
		head = head->next;
		i++;
	}
	return (args);
}

t_tkn *last_before_cmd(t_tkn *head)
{
	while (head && head->type == WORD)
		head = head->next;
	while (head && head->type == OP_STOP
		&& head->next && head->next->type == OP_STOP)
		head = head->next;
	return (head);
}

void execute_cd(t_cmd *cmd)
{
	int i = 0;
	while (cmd->args[i])
		i++;
	if (i != 2)
		ft_putstr_fd(2, "cd: wrong arguments\n");
	else
	{
		int res = chdir(cmd->args[1]);
		if (res == -1)
			ft_putstr_fd(2, "cd: can't change dir\n");
	}
}

void execute_cmd(t_cmd *cmd, char **envp)
{
	if (!strncmp(cmd->path, "cd", 3))
	{
		execute_cd(cmd);
		return;
	}
	
	if (cmd->path[0] != '/')
	{
		size_t path_len = ft_strlen(cmd->path);
		char *new_path = ft_calloc(3 + path_len);
		new_path[0] = '.';
		new_path[1] = '/';
		size_t i = 0;
		while (i < path_len)
		{
			new_path[i + 2] = cmd->path[i];
			i++;
		}
		free(cmd->path);
		cmd->path = new_path;
	}

	pid_t new_pid = fork();
	// error
	if (new_pid == -1)
	{
		ft_putstr_fd(2, "can't fork... too bad\n");
		exit(1);
	}
	// child
	if (new_pid == 0)
	{
		int result = execve(cmd->path, cmd->args, envp);
		if (result == -1)
		{
			ft_putstr_fd(2, "can't execute... too bad\n");
			exit(1);
		}
	}
	// parent
	else
	{
		int stat_loc = 0;
		waitpid(new_pid, &stat_loc, 0);
	}
}

void executor(t_tkn *head, char **envp)
{
	t_tkn *prev = NULL;
	int stdin_copy = ft_dup(0);
	int stdout_copy = ft_dup(1);

	while (head)
	{
		t_cmd *cmd = ft_calloc(sizeof(t_cmd));
		cmd->path = ft_strdup(head->str);
		cmd->args = ft_set_args(head);

		if (prev && prev->type == OP_PIPE)
			cmd->redir_in = true;
		
		prev = last_before_cmd(head);
		if (prev && prev->type == OP_PIPE)
			cmd->redir_out = true;
		
		redir(cmd, stdin_copy, stdout_copy);
		execute_cmd(cmd, envp);

		if (prev)
			head = prev->next;
		else
			head = NULL;
	}
}
