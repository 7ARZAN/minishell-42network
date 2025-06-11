/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_split_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr <yel-hadr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 05:07:33 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/10/12 05:30:14 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

char	*find_next_argument(char *cmd)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (cmd[i] && (!ft_strchr("\t |<>", cmd[i]) || sq || dq))
	{
		if (cmd[i] == '\'' && !dq)
			sq = !sq;
		else if (cmd[i] == '\"' && !sq)
			dq = !dq;
		i++;
	}
	return (cmd + i);
}

int	args_count(char *cmd)
{
	int	count;

	count = 0;
	while (*cmd)
	{
		if (!ft_strchr("\t |<>", *cmd))
		{
			count++;
			cmd = find_next_argument(cmd);
		}
		else if (ft_strchr("><", *cmd))
		{
			while (ft_strchr("><", *cmd))
				cmd++;
		}
		else
			cmd++;
	}
	return (count);
}

int	extract_redir_file(char *input, t_cmd *cmd, t_redir_type type, t_list *env)
{
	char	*tmp;
	int		i;

	i = 0;
	if (type == NONE)
		return (0);
	if ((type == REDIR_OUT || type == APPEND) && cmd->redir_out.file)
		free(cmd->redir_out.file);
	else if ((type == REDIR_IN || type == HEREDOC) && cmd->redir_in.file)
		free(cmd->redir_in.file);
	tmp = ft_substr(input, 0, ft_strlen(input) - ft_strlen(find_next_argument(input)));
	if (type == REDIR_OUT || type == APPEND)
	{
		cmd->redir_out.file = remove_quotes(tmp);
		i = open_redir_file(cmd->redir_out.file, type);
	}
	else if (type == REDIR_IN)
	{
		cmd->redir_in.file = remove_quotes(tmp);
		i = open_redir_file(cmd->redir_in.file, type);
	}
	else if (type == HEREDOC)
		cmd->redir_in.file = get_heredoc(tmp, env);
	free(tmp);
	return (i);
}
