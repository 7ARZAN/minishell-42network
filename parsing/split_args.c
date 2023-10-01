/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:41:52 by elakhfif          #+#    #+#             */
/*   Updated: 2023/10/01 01:36:12 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static char	*next_arg(char *cmd)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (cmd[i] && (cmd[i] != ' ' || sq || dq))
	{
		if (cmd[i] == '\'' && !dq)
			sq = !sq;
		else if (cmd[i] == '\"' && !sq)
			dq = !dq;
		i++;
	}
	return (cmd + i);
}

static int	args_count(char *cmd)
{
	int	count;

	count = 0;
	while (*cmd)
	{
		if (!ft_strchr("\t |<>", cmd[0]))
		{
			count++;
			cmd = next_arg(cmd);
		}
		else if (ft_strchr("><", cmd[0]))
		{
			while (ft_strchr("><", cmd[0]))
				cmd++;
		}
		else
			cmd++;
	}
	return (count);
}

int	ft_get_redir_file(char *input, t_cmd *cmd, t_redir_type type)
{
	int		i;
	char	*tmp;

	i = 0;
	if (type == NONE)
		return (0);
	if ((type == REDIR_OUT || type == APPEND) && cmd->redir_out.file)
		free(cmd->redir_out.file);
	else if ((type == REDIR_IN || type == HEREDOC) && cmd->redir_in.file)
		free(cmd->redir_in.file);
	tmp = ft_substr(input, 0, ft_strlen(input) - ft_strlen(next_arg(input)));
	if (type == REDIR_OUT || type == APPEND)
	{
		cmd->redir_out.file = remove_quotes(tmp);
		i = ft_redir_open(cmd->redir_out.file, type, cmd);
	}
	else if (type == REDIR_IN || type == HEREDOC)
	{
		cmd->redir_in.file = remove_quotes(tmp);
		i = ft_redir_open(cmd->redir_in.file, type, cmd);
	}
	return (i);
}

static void	redir_init(t_cmd *command)
{
	command->redir_in.type = NONE;
	command->redir_out.type = NONE;
	command->redir_in.file = NULL;
	command->redir_out.file = NULL;
}

static void	ft_skip_spaces(char **cmd)
{
	while (ft_strchr(" \t", **cmd))
		(*cmd)++;
}
char	**split_args(char *cmd, t_cmd *command)
{
	int		index;
	int		count;
	char	*tmp;
	char	**result;

	(void)command;
	index = 0;
	count = args_count(cmd);
	result = ft_calloc(count + 1, sizeof(char *));
	redir_init(command);
	while (count)
	{
		while (cmd[0] && ft_strchr("\t ", cmd[0]))
			cmd++;
		if (ft_strchr(">", *cmd))
		{
			command->redir_out.type = get_redir_type(cmd);
			while (ft_strchr("> \t", *cmd))
				cmd++;
			ft_get_redir_file(cmd, command, command->redir_out.type);
			count--;
		}
		else if (ft_strchr("<", *cmd))
		{
			command->redir_in.type = get_redir_type(cmd);
			while (ft_strchr("< \t", *cmd))
				cmd++;
			ft_get_redir_file(cmd, command, command->redir_in.type);
			count--;
		}
		else
		{
			tmp = next_arg(cmd);
			result[index] = ft_substr(cmd, 0, ft_strlen(cmd) - ft_strlen(tmp));
			cmd = tmp;
			index++;
			count--;
		}
		ft_skip_spaces(&cmd);
	}
	return (result);
}

// int	main(void)
// {
// 	char	*cmd;
// 	char	**args;
// 	int		i;
//
// 	cmd = "echo \"hello world\" > file";
// 	args = split_args(cmd);
// 	i = 0;
// 	while (args[i])
// 	{
// 		printf("%s\n", args[i]);
// 		i++;
// 	}
// 	return (0);
// }
