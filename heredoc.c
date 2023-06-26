/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 06:30:14 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/26 06:49:26 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//read from stdin until EOF and return the string !
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

//heredoc function : read from stdin until EOF and write it to a file
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

//heredoc_handler : check if there is a heredoc in the command and call heredoc function
//then replace the heredoc with the file path
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

// int	main(void)
// {
// 	t_cmd	cmd;
//
// 	cmd.args = malloc(sizeof(char *) * 3);
// 	cmd.args[0] = ft_strdup("<<");
// 	cmd.args[1] = ft_strdup("EOF");
// 	heredoc_handler(&cmd);
// 	return (0);
// }
