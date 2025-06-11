/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:46:27 by elakhfif          #+#    #+#             */
/*   Updated: 2023/10/13 08:05:43 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static void	init_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->redir_in.file = NULL;
	cmd->redir_out.file = NULL;
	cmd->redir_in.type = NONE;
	cmd->redir_out.type = NONE;
}

static int	process_cmd(t_cmd **cmd_list, char **line, t_list *env, int *status)
{
	char	*expanded_line;
	int		has_processed;

	has_processed = 0;
	if (ft_strchr(*line, '$') && !ft_strchr(*line, '\''))
	{
		expanded_line = expand_variable(*line, env, status);
		*line = expanded_line;
		has_processed = 1;
	}
	*status = 0;
	*cmd_list = split_cmd(*line, status);
	if (*cmd_list)
		has_processed = 1;
	return (has_processed);
}

t_cmd	*parser(char *line, t_list *env, int *status)
{
	t_cmd	*result;
	t_cmd	*tmp;

	g_sig = -1;
	if (!line || !*line)
		return (NULL);
	result = NULL;
	if (!process_cmd(&result, &line, env, status) && !*status)
		ft_putstr_fd(TOKENERR, 2);
	tmp = result;
	while (tmp)
	{
		init_cmd(tmp);
		*status = split_args(tmp, env);
		tmp = tmp->next;
	}
	free(line);
	if (g_sig == -1)
		g_sig = 0;
	return (result);
}
