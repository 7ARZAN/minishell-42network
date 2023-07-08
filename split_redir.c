/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 06:30:14 by elakhfif          #+#    #+#             */
/*   Updated: 2023/07/08 17:57:05 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*get_redir_symbol(char *symbol)
{
	int	skip;

	if (!symbol)
		return (NULL);
	skip = 1;
	if (symbol[0] && symbol[1] && symbol[0] == symbol[1])
		skip = 2;
	symbol += skip;
	return (symbol);
}

static int	checking_redir(t_cmd *cmd)
{
	int	i;
	int	len;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (cmd->redir_symbols[++i] && !tmp)
	{
		len = ft_strlen(cmd->redir_symbols[i]);
		if (len <= 2 && (!ft_strncmp("<<", cmd->redir_symbols[i], len) || !ft_strncmp(">>", cmd->redir_symbols[i], len)))
		{
			if (cmd->redir_files[i + 1] == NULL)
				tmp = "syntax error near unexpected token `newline'";
		}
		else
			tmp = get_redir_symbol(cmd->redir_symbols[i]);
	}
	if (tmp)
		{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	return (1);
}

int	split_redir(t_cmd *cmd)
{
	int	lenth;
	int	i;
	char	**get_redir;

	i = -1;
	lenth = 0;
	get_redir = get_redirections(cmd->cmd);
	while (get_redir[++i])
		lenth++;
	cmd->redir_files = (char **)malloc(sizeof(char *) * (lenth + 1));
	cmd->redir_symbols = (char **)malloc(sizeof(char *) * (lenth + 1));
	i = -1;
	while (get_redir[++i])
	{
		cmd->redir_files[i] = get_redir[i];
		cmd->redir_symbols[i] = get_redir_symbol(get_redir[i]);
	}
	cmd->redir_files[i] = NULL;
	cmd->redir_symbols[i] = NULL;
	free(get_redir);
	return (checking_redir(cmd));
}
