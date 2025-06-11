/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:41:52 by elakhfif          #+#    #+#             */
/*   Updated: 2023/10/13 06:30:49 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static char	*extract_argument(char *cmd, int *count)
{
	char	*tmp;
	char	*result;

	tmp = ft_substr(cmd, 0, (ft_strlen(cmd) - ft_strlen(find_next_argument(cmd))));
	result = remove_quotes(tmp);
	(*count)--;
	free(tmp);
	return (result);
}

static int	handle_outfile(char **cmd, t_cmd *cmd_struct, t_list *env, int *count)
{
	cmd_struct->redir_out.type = get_redir_type(*cmd);
	if (cmd_struct->redir_out.type == ERROR)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
		return (1);
	}
	while (ft_strchr("> \t", **cmd))
		(*cmd)++;
	if (extract_redir_file(*cmd, cmd_struct, cmd_struct->redir_out.type, \
		env) == -1)
	{
		ft_error(cmd_struct->redir_out.file, strerror(errno));
		return (1);
	}
	(*count)--;
	return (0);
}

static int	handle_infile(char **cmd, t_cmd *cmd_struct, t_list *env, int *count)
{
	cmd_struct->redir_in.type = get_redir_type(*cmd);
	if (cmd_struct->redir_in.type == ERROR)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
		return (1);
	}
	while (ft_strchr("< \t", **cmd))
		(*cmd)++;
	if (extract_redir_file(*cmd, cmd_struct, cmd_struct->redir_in.type, \
		env) == -1)
	{
		ft_error(cmd_struct->redir_in.file, strerror(errno));
		return (1);
	}
	(*count)--;
	return (0);
}

int	split_args(t_cmd *command, t_list *env)
{
	int		count;
	char	*cmd;
	int		index;

	index = 0;
	count = args_count(command->cmd);
	command->args = ft_calloc(count + 1, sizeof(char *));
	if (!command->args)
		return (1);
	cmd = command->cmd;
	while (count)
	{
		cmd += skip_wspace(cmd, 0);
		if (ft_strchr("><", *cmd))
		{
			if (((*cmd == '>' && handle_outfile(&cmd, command, env, &count))
					|| (*cmd == '<' && handle_infile(&cmd, command, env, \
					&count))))
				return (1);
		}
		else
			command->args[index++] = extract_argument(cmd, &count);
		cmd = find_next_argument(cmd);
	}
	return (0);
}
