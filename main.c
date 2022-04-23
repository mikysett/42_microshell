#include "ft_microshell.h"

int main(int argc, char **argv, char **envp)
{
	t_tkn **tokens = ft_calloc(sizeof(t_tkn *));

	parser(tokens, argc, argv);
	executor(*tokens, envp);
	return (0);
}