/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 06:30:14 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/26 07:51:09 by elakhfif         ###   ########.fr       */
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
	char	*input;
	int		fd;

	input = read_heredoc(eof);
	fd = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	write(fd, input, ft_strlen(input));
	close(fd);
}

//heredoc_handler : check if there is a heredoc in the command and call heredoc function
//then replace the heredoc with the file path
void		heredoc_handler(t_cmd *cmd)
{
	int	i;
	char	*eof;
	char	*tmp;

	i = 0;
	while (cmd->args[i])
	{
		if (!ft_strcmp(cmd->args[i], "<<"))
		{
			eof = cmd->args[i + 1];
			heredoc(cmd, eof);
			tmp = ft_strdup("/tmp/heredoc");
			free(cmd->args[i]);
			cmd->args[i] = tmp;
			cmd->heredoc = tmp;
			cmd->args[i + 1] = NULL;
			break ;
		}
		i++;
	}
}

int	main(void)
{
	t_cmd	cmd;

	cmd.heredoc = NULL;
	cmd.args = ft_split("cat << EOF", ' ');
	heredoc_handler(&cmd);
}
