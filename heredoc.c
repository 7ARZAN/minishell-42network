/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 06:30:14 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/26 06:38:23 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*read_heredoc(char *eof)
{
	char	*line;
	char	*tmp;
	char	*tmp2;

	line = NULL;
	while (1)
	{
		tmp = line;
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, eof))
		{
			free(line);
			break ;
		}
		tmp2 = ft_strjoin(line, "\n");
		free(line);
		line = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
	}
	return (line);
}

static void	heredoc(t_cmd *cmd, char *eof)
{
	char	*line;
	int		fd;

	line = read_heredoc(eof);
	fd = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	write(fd, line, ft_strlen(line));
	close(fd);
	cmd->heredoc = ft_strdup("/tmp/heredoc");
}

void		heredoc_handler(t_cmd *cmd)
{
	int		i;
	char	*eof;

	i = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '<' && cmd->args[i][1] == '<')
		{
			eof = ft_strdup(cmd->args[i + 1]);
			heredoc(cmd, eof);
			free(eof);
			free(cmd->args[i]);
			free(cmd->args[i + 1]);
			cmd->args[i] = ft_strdup("<");
			cmd->args[i + 1] = ft_strdup("/tmp/heredoc");
		}
		i++;
	}
	free(cmd->args[i]);
}

int	main(void)
{
	t_cmd	cmd;

	cmd.args = malloc(sizeof(char *) * 4);
	cmd.args[0] = ft_strdup("cat");
	cmd.args[1] = ft_strdup("<<");
	cmd.args[2] = ft_strdup("EOF");
	cmd.args[3] = NULL;
	heredoc_handler(&cmd);
	return (0);
}
