/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:56:11 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/23 06:37:24 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	print_error(char *str)
{
	ft_putstr_fd("Minishell: syntax error near unexpected token `|", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
}

static char	*get_separator(char *str)
{
	int		index[3];
	char	*result;

	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	result = ft_calloc(3, 1);
	while (str[0])
	{
		if ((!(index[1] & 1) && !(index[2] & 1)))
		{
			if (str[1] && ft_strchr("><", str[0]) && ft_strchr("|", str[1]))
				str++;
			else if (ft_strchr("|", str[0]))
			{
				result[index[0]++] = str[0];
				result = realloc(result, index[0] + 2);
			}
		}
		index[1] += (!(index[2] & 1) && str[0] == '"');
		index[2] += (!(index[1] & 1) && str[0] == '\'');
		str++;
	}
	return (result);
}

int	check_separator(t_cmd *cmd)
{
	char	*temp;

	while (cmd)
	{
		temp = get_separator(cmd->cmd);
		if (ft_strlen(temp) == ft_strlen(cmd->cmd)
			|| (temp[0] == '|' && !cmd->next))
		{
			print_error(temp);
			free(temp);
			return (1);
		}
		cmd->sep = ft_strdup(temp);
		free(temp);
		cmd = cmd->next;
	}
	return (0);
}
