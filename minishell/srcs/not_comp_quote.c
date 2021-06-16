#include "../minishell.h"

int	quote_error(void)
{
	ft_putstr("Minishell: syntax error: unexpected end of file \n");
	return (-1);
}

int	not_comp_quote(char *line)
{
	int	i;
	int	sngl;
	int	dbl;

	i = 0;
	sngl = 0;
	dbl = 0;
	while (line[i])
	{
		if (line[i] == '\\' && line[i + 1] != '\'' && ++i)
			i++;
		if (line[i] == '\"' && dbl == 0 && sngl == 0)
			dbl = 1;
		else if (line[i] == '\"' && dbl == 1 && sngl == 0)
			dbl = 0;
		else if (line[i] == '\'' && dbl == 0 && sngl == 0)
			sngl = 1;
		else if (line[i] == '\'' && sngl == 1 && dbl == 0)
			sngl = 0;
		i++;
	}
	if (sngl == 1 || dbl == 1)
		return (quote_error());
	return (0);
}
