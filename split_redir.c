/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 08:40:56 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/15 09:01:28 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	initiate_redir(t_redir *redir, int size)
{
	redir->redir_files = ft_calloc(size + 1, sizeof(char *));
	redir->redir_type = ft_calloc(size + 1, sizeof(char *));
}

static char	*redir_type(char *type)
{
	int	first;
	int	second;

	if (!type)
		return (NULL);
	first = 0;
	second = 0;
	while (type[first] && (type[first] != '>' || type[first] != '<'))
		first++;
	if (type[first] == '>' || type[first] == '<')
	{
		second = first + 1;
		if (type[second] == '>' || type[second] == '<')
		{
			if (type[second] == '>')
				return (ft_strdup(">>"));
			else
				return (ft_strdup("<<"));
		}
		else
		{
			if (type[first] == '>')
				return (ft_strdup(">"));
			else
				return (ft_strdup("<"));
		}
	}
	return (NULL);
}

static int	check_redir(t_cmd *cmd)
{
	int	i;
	int	len;
	char	*type;

	i = 0;
	len = 0;
	while (cmd->args[i])
	{
		type = redir_type(cmd->args[i]);
		if (type)
		{
			len++;
			free(type);
		}
		i++;
	}
	return (len);
}

int	split_redir(t_cmd *cmd)
{
