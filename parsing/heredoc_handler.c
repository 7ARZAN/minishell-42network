/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 03:21:35 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/10/13 05:00:40 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static int	needs_expansion(char *delim)
{
	if (!delim || !ft_strchr(delim, '$'))
		return (0);
	while (*delim)
	{
		if (ft_strchr("\'\"", *delim))
			return (1);
		delim++;
	}
	return (0);
}

static char	*strip_heredoc_quotes(char *delim)
{
	char	*unquoted_delim;

	if (!delim || (!ft_strchr(delim, '\'') && !ft_strchr(delim, '\"')))
		return (delim);
	unquoted_delim = remove_quotes(delim);
	free(delim);
	return (unquoted_delim);
}

static char	*read_heredoc(char *delim, int expand, t_list *env)
{
	char	*content;
	char	*line;

	content = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delim) || g_sig == -2)
		{
			free(line);
			break ;
		}
		if (expand && ft_strchr(line, '$'))
			line = expand_variable(line, env, NULL);
		content = ft_strjoin_free(content, line);
		content = ft_strjoin_free(content, "\n");
		free(line);
	}
	return (content);
}

char	*get_heredoc(char *delim, t_list *env)
{
	char	*content;
	int		expand;

	if (!delim || g_sig == -2)
		return (NULL);
	expand = !needs_expansion(delim);
	delim = strip_heredoc_quotes(delim);
	content = read_heredoc(delim, expand, env);
	return (content);
}
