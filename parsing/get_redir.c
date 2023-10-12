/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr <yel-hadr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:17:38 by elakhfif          #+#    #+#             */
/*   Updated: 2023/10/12 16:58:28 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static t_redir_type	check_redir_out(char *input)
{
	int				i;
	t_redir_type	type;

	i = 0;
	type = NONE;
	while (input[i])
	{
		if (input[i] == '>')
		{
			type = REDIR_OUT;
			i++;
			skip_wspaces(input, &i);
			if (input[i] == '<' || !*input)
				return (ERROR);
			if (input[i] == '>')
				type = APPEND;
			i++;
			skip_wspaces(input, &i);
			if (!*input || ft_strchr("<>", input[i]))
				type = ERROR;
			return (type);
		}
		i++;
	}
	return (type);
}

static t_redir_type	check_redir_in(char *input)
{
	int				i;
	t_redir_type	type;

	i = 0;
	type = NONE;
	while (input[i])
	{
		if (input[i] == '<')
		{
			type = REDIR_IN;
			i++;
			skip_wspaces(input, &i);
			if (input[i] == '>' || !*input)
				return (ERROR);
			if (input[i] == '<')
				type = HEREDOC;
			i++;
			if (!*input || ft_strchr("<>", input[i]))
				type = ERROR;
			return (type);
		}
		i++;
	}
	return (type);
}

t_redir_type	get_redir_type(char *input)
{
	int				i;
	t_redir_type	type;

	i = 0;
	type = NONE;
	while (input[i])
	{
		if (input[i] == '>')
			return (check_redir_out(input));
		if (input[i] == '<')
			return (check_redir_in(input));
		i++;
	}
	return (type);
}

int	ft_redir_open(char *file, t_redir_type type)
{
	int	fd;

	fd = 0;
	if (type == REDIR_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == REDIR_IN)
		fd = open(file, O_RDONLY);
	if (fd != -1 && type != HEREDOC)
		close(fd);
	return (fd);
}
