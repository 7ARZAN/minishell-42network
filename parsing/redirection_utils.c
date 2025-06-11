/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:17:38 by elakhfif          #+#    #+#             */
/*   Updated: 2023/10/13 04:49:58 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	skip_wspace(char *input, int i)
{
	while (input[i] && ft_isspace(input[i]))
		i++;
	return (i);
}

static t_redir_type	check_output_redir(char *input, int current)
{
	t_redir_type	type;

	type = REDIR_OUT;
	current++;
	if (!input[current] || input[current++] == '>')
		type = APPEND;
	current = skip_wspace(input, current);
	if (!input[current] || ft_strchr("<>|", input[current]))
		type = ERROR;
	return (type);
}

static t_redir_type	check_input_redir(char *input, int current)
{
	t_redir_type	type;

	type = REDIR_IN;
	current++;
	if (!input[current] || input[current++] == '<')
		type = HEREDOC;
	current = skip_wspace(input, current);
	if (!input[current] || ft_strchr("<>|", input[current]))
		type = ERROR;
	return (type);
}

t_redir_type	get_redir_type(char *input)
{
	int				current;

	current = 0;
	while (input[current])
	{
		if (input[current] == '>')
			return (check_output_redir(input, current));
		if (input[current] == '<')
			return (check_input_redir(input, current));
		current++;
	}
	return (NONE);
}

int	open_redir_file(char *filename, t_redir_type type)
{
	int	fd;

	fd = 0;
	if (type == REDIR_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == REDIR_IN)
		fd = open(filename, O_RDONLY);
	if (fd != -1 && type != HEREDOC)
		close(fd);
	return (fd);
}
