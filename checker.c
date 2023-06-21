/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:56:11 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/21 12:09:45 by elakhfif         ###   ########.fr       */
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
	int	index;
	int	dq;
	int	sq;
	char	*separator;

	index = 0;
	dq = 0;
	sq = 0;
	separator = ft_calloc(2, sizeof(char));
	while (str && str[0])
	{
		if (dq && !sq)
		{
			if(str[1] && ft_strchr("><", str[0]) && ft_strchr("|", str[1]))
				str++;
			else if (ft_strchr("|", str[0]))
			{
				separator[index++] = str[0];
				separator = realloc(separator, (index + 2) * sizeof(char));
			}
		}
		dq += (str[0] == '\"') ? 1 : 0;
		sq += (str[0] == '\'') ? 1 : 0;
		str++;
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
		if (ft_strlen(tmp) == ft_strlen(cmd->cmd) || (tmp[0] == '|' && !cmd->next))
		{
			syntax_error(cmd->cmd);
			free(tmp);
			return (1);
		}
		cmd->sep = ft_strdup(tmp);
		cmd = cmd->next;
	}
	return (0);
}

int	main()
{
	char *str = "echo \"hello\" | cat -e | cat -e | cat -e";
	t_cmd *cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->cmd = ft_strdup(str);
	check_separator(cmd);
	while (cmd)
	{
		printf("cmd:\t%s\n", cmd->cmd);
		printf("sep:\t%s\n", cmd->sep);
		cmd = cmd->next;
	}
}
