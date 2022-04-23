#include "ft_microshell.h"

t_tkn_type get_type(char *str)
{
	if (ft_strlen(str) == 1)
	{
		if (*str == '|')
			return (OP_PIPE);
		if (*str == ';')
			return (OP_STOP);
	}
	return (WORD);
}

void parser(t_tkn **tokens, int argc, char **argv)
{
	int i = 1;

	while (i < argc)
	{
		t_tkn *new_tkn = ft_calloc(sizeof(t_tkn));
		new_tkn->type = get_type(argv[i]);
		new_tkn->str = ft_strdup(argv[i]);
		ft_pushback(tokens, new_tkn);
		i++;
	}
}
