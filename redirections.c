/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:17:38 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/19 23:40:12 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//init_redir is a function that initializes the redirections
void	init_redir(t_redir *redir)
{
	redir->redir_files = NULL;
	redir->redir_type = 0;
}

//ms_parse_redir is a function that parses the redirections
static int	ms_detect_redir_type(char *str)
{
	if (str[0] == '>' && str[1] == '>')
		return (APPEND);
	else if (str[0] == '>')
		return (REDIR_OUT);
	else if (str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	else if (str[0] == '<')
		return (REDIR_IN);
	return (0);
}

static char	*ms_get_redir_files(char *str)
{
	int		i;
	int		j;
	char	*redir_files;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '>' && str[i] != '<')
		i++;
	if (!(redir_files = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (j < i)
	{
		redir_files[j] = str[j];
		j++;
	}
	redir_files[j] = '\0';
	return (redir_files);
}


//ms_add_redir is a function that adds redirections to the linked list of redirections
static void	ms_add_redir(t_cmd *cmd, t_redir *redir)
{
	t_redir	*tmp;

	if (!cmd->redir)
		cmd->redir = redir;
	else
	{
		tmp = cmd->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

//ms_parse_redir is a function that parses the redirections
int	ms_parse_redir(t_cmd *cmd, t_redir *redir)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = cmd->cmd;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			redir->redir_type = ms_detect_redir_type(&str[i]);
			redir->redir_files = ms_get_redir_files(&str[i]);
			ms_add_redir(cmd, redir);
			return (i);
		}
		i++;
	}
	return (0);
}
// int	main(int argc, char **argv)
// {
// 	t_cmd	cmd;
// 	t_redir	redir;
//
// 	cmd.cmd = argv[1];
// 	init_redir(&redir);
// 	ms_parse_redir(&cmd, &redir);
// 	while (cmd.redir)
// 	{
// 		printf("redir_type: %d\n", cmd.redir->redir_type);
// 		printf("redir_files: %s\n", cmd.redir->redir_files);
// 		if (!cmd.redir->next)
// 			break ;
// 		cmd.redir = cmd.redir->next;
// 	}
// 	return (0);
// }
