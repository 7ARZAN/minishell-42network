/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:56:11 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/21 11:01:03 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	syntax_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
}

static char	*get_separator(char *str)
{
	int	i;
	int	index;
	int	dq;
	int	sq;
	char	*separator;

	i = 0;
	index = 0;
	dq = 0;
	sq = 0;
	separator = ft_calloc(2, sizeof(char));
	while (str && str[i])
	{
		if (dq && !sq)
		{
			if(str[1] && ft_strchr("><", str[i]) && ft_strchr("|", str[i + 1]))
				i++;
			else if (ft_strchr("|", str[i]))
			{
				separator[index++] = str[i];
				separator = realloc(separator, (index + 2) * sizeof(char));
			}
		}
		dq += (str[i] == '\"') ? 1 : 0;
		sq += (str[i] == '\'') ? 1 : 0;
		i++;
	}
	return (separator);
}


int	check_separator(t_cmd *cmd)
{
	int	i;
	char	*tmp;

	i = 0;
	tmp = get_separator(cmd->cmd);
	while (cmd)
	{
		if (ft_strchr(tmp, cmd->sep[i]))
			i++;
		else
		{
			syntax_error(cmd->sep);
			free(tmp);
			return (0);
		}
		cmd = cmd->next;
	}
	return (1);
}

int	main()
{
	int	i;
	char	*str;

	i = 0;
	str = ft_strdup("echo \"hello\" | cat -e > file");
	char **tab = ft_split(str, '|');
	while (tab[i])
	{
		printf("tab[%d] = %s\n", i, tab[i]);
		i++;
	}
	printf("tab[%d] = %s\n", i, tab[i]);
	return (0);
}
