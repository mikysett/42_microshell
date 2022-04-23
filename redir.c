#include "ft_microshell.h"
#include <stdio.h>

void redir(t_cmd *cmd, int stdin_copy, int stdout_copy)
{
	static int pipes[2];
	static bool has_redir_in = false;
	static bool has_redir_out = false;

	if (cmd->redir_in)
	{
		has_redir_in = true;
		close(pipes[1]);
		ft_dup2(pipes[0], 0);
		close(pipes[0]);
	}
	else if (has_redir_in)
	{
		has_redir_in = false;
		ft_dup2(stdin_copy, 0);
	}

	if (cmd->redir_out)
	{
		has_redir_out = true;
		ft_pipe(pipes);
		ft_dup2(pipes[1], 1);
	}
	else if (has_redir_out)
	{
		has_redir_out = false;
		ft_dup2(stdout_copy, 1);
	}
}