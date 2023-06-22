/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:17:38 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/22 02:30:09 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//init_redir is a function that initializes the redirections
void	init_redir(t_redir *redir)
{
	redir->redir_files = NULL;
	redir->redir_symbols = 0;
}

//detect_redir is a function that detects the redirections symbols

static char	*ms_detect_symbol(char *symbl)
{
	int	i;

	if (!symbl)
		return (NULL);
	i = 1;
	if (symbl[0] && symbl[1] && symbl[0] == symbl[1])
		i++;
	symbl += i;
	return (symbl);
}

static int	ms_checker(t_cmd *cmd)
{
	int	i;
	int	length;
	char	*tmp;

	i = -1;
	tmp = NULL;
	length = ft_strlen(cmd->cmd);
	while (++i < length)
	{
		if (length <= 2 && (!ft_strncmp(cmd->cmd + i, ">>", 2) || !ft_strncmp(cmd->cmd + i, "<<", 2)))
		{
			tmp = ms_detect_symbol(cmd->cmd + i);
			break ;
		}
		else if (cmd->cmd[i] == '>' || cmd->cmd[i] == '<')
		{
			tmp = cmd->cmd + i;
			break ;
		}
	}
	return (ft_strcmp(tmp, ">>") && ft_strcmp(tmp, "<<") && ft_strcmp(tmp, ">") && ft_strcmp(tmp, "<"));
}

int	ms_redirections(t_cmd *cmd)
{
	int	i[2];
	int	length;
	char	**extract_redi;

	while (cmd)
	{
		i[0] = 0;
		i[1] = 0;
		extract_redi = extract_redir(cmd->cmd);
		length = ft_strlen(cmd->cmd);
		init_redir(cmd->redir);
		while(++i[0] <= length)
		{
			cmd->redir->redir_files = ft_split(cmd->cmd + i[1], ' ');
			i[1] = i[0];
		}
		if (ms_checker(cmd))
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

t_cmd	*ms_cmd(char *cmd, t_cmd *cmd_list)
{
	t_cmd	*new_cmd;
	t_cmd	*tmp;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	new_cmd->cmd = ft_strdup(cmd);
	new_cmd->redir = (t_redir *)malloc(sizeof(t_redir));
	new_cmd->next = NULL;
	if (!cmd_list)
		return (new_cmd);
	tmp = cmd_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
	return (cmd_list);
}

int	main(int ac, char **av)
{
	t_cmd	*cmd;
	int	i;

	i = 0;
	cmd = NULL;
	while (++i < ac)
		cmd = ms_cmd(av[i], cmd);
	ms_redirections(cmd);
	while (cmd)
	{
		printf("cmd: %s\n", cmd->cmd);
		printf("redir: %s\n", cmd->redir->redir_files[0]);
		cmd = cmd->next;
	}
	return (0);
}

