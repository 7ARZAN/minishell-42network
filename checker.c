/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:56:11 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/19 02:18:16 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	syntax_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
}

static char	*get_sepator(char *str)
{
	int		i;
	char	*sep;

	i = 0;
	while (str[i] && !ft_strchr("><|", str[i]))
		i++;
	sep = ft_substr(str, 0, i);
	return (sep);
}

int	checker(t_cmd *cmd)
{
	int		i;
	char	*sep;

	i = 0;
	while (cmd->args[i])
	{
		sep = get_sepator(cmd->args[i]);
		if (ft_strchr("><|", cmd->args[i][0]) && ft_strlen(sep) == 1)
		{
			if (ft_strlen(cmd->args[i]) == 1)
			{
				syntax_error(cmd->args[i]);
				return (0);
			}
			else if (ft_strlen(cmd->args[i]) == 2 && cmd->args[i][1] == '>')
			{
				syntax_error(cmd->args[i]);
				return (0);
			}
		}
		i++;
	}
	return (1);
}
