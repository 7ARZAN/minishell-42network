/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:46:27 by elakhfif          #+#    #+#             */
/*   Updated: 2023/07/10 20:31:36 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*parser(char *line)
{
	t_cmd	*result;
	t_cmd	*cmd;

	if (!line)
		return (NULL);
	result = split_cmd(line);
	cmd = result;
	while (cmd)
	{
		cmd->args = split_args(cmd->cmd);
		cmd = cmd->next;
	}
	return (result);
}


