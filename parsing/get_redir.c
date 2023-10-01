/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:17:38 by elakhfif          #+#    #+#             */
/*   Updated: 2023/09/30 22:43:59 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_redir_type	get_redir_type(char *input)
{
	t_redir_type	type;
	int		i;
	int		sq;
	int		dq;

	i = 0;
	sq = 0;
	dq = 0;
	type = NONE;
	while (input && input[i])
	{
		if (input[i] == '\'' && !dq)
			sq = !sq;
		if (input[i] == '\"' && !sq)
			dq = !dq;
		if (input[i] == '>' && !sq && !dq)
		{
			type = REDIR_OUT;
			if (input[i + 1] == '>')
				type = APPEND;
			return (type);
		}
		if (input[i] == '<' && !sq && !dq)
		{
			type = REDIR_IN;
			if (input[i + 1] == '<')
				type = HEREDOC;
			return (type);
		}
		i++;
	}
	return (type);
}

char	*ft_get_heredoc(char *heredoc)
{
	char	*tmp;
	char	*line;

	tmp = NULL;
	line = NULL;
	while (1)
	{
		line = readline("[42heredoc] > ");
		if (!ft_strcmp(line, heredoc))
			break ;
		tmp = ft_strjoin(tmp, line);
		tmp = ft_strjoin(tmp, "\n");
		free(line);
	}
	return (tmp);
}

int	ft_redir_open(char *file, t_redir_type type, t_cmd *cmd)
{
	int	fd;

	fd = 0;
	if (type == REDIR_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == REDIR_IN)
		fd = open(file, O_RDONLY);
	else if (type == HEREDOC)
		cmd->redir_in.file = ft_get_heredoc(file);
	if (type == HEREDOC)
		free(file);
	if (fd != -1 && type != HEREDOC)
		close(fd);
	return (fd);
}
