/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:56:11 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/22 05:42:40 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*check_separator(char *str)
{
	t_cmd	*cmd;
	t_cmd	*head;
	int		i;

	i = 0;
	cmd = malloc(sizeof(t_cmd));
	head = cmd;
	while (str[i] && str)
	{
		if (ft_strchr("|&", str[i]))
		{
			cmd->cmd = ft_substr(str, 0, i);
			str = str + i + 1;
			cmd->next = malloc(sizeof(t_cmd));
			cmd = cmd->next;
			i = 0;
		}
		i++;
	}
	cmd->cmd = ft_substr(str, 0, i);
	cmd->next = NULL;
	return (head);
}
