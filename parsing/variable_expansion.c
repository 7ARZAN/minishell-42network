/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr <yel-hadr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 09:52:20 by elakhfif          #+#    #+#             */
/*   Updated: 2023/10/12 04:16:37 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*extract_var_name(char *input, int end, int start)
{
	char	*var_name;
	int		current;

	var_name = ft_calloc((end - start + 1), sizeof(char));
	if (!var_name)
		return (NULL);
	current = 0;
	while (start < end)
		var_name[current++] = input[start++];
	var_name[current] = '\0';
	return (var_name);
}

static int	is_heredoc_delim(char *input, int current, int *status)
{
	int	pos;

	if (!input || !status || !current)
		return (0);
	pos = (input[current] == '$') ? current - 1 : current;
	while (pos && ft_strchr(" \t", input[pos]))
		pos--;
	return (pos > 0 && input[pos] == '<' && input[pos - 1] == '<');
}

static int	expand_status(char **result, char next_char, int *exit_status, int *index)
{
	char	*status_str;

	if (next_char != '?')
		return (1);
	status_str = ft_itoa(*exit_status);
	if (!status_str)
		return (1);
	*result = ft_strjoin_free(*result, status_str);
	free(status_str);
	*index += 2;
	return (0);
}

static int	expand_env_var(char *input, char **result, int current, t_list *env)
{
	char	*var_name;
	char	*var_value;
	int		start;

	start = current + 1;
	current = next_var(input, current + 1);
	var_name = extract_var_name(input, current, start);
	if (!var_name)
		return (current);
	var_value = ft_getval(var_name, env);
	if (!var_value)
		var_value = ft_strdup("");
	*result = ft_strjoin_free(*result, var_value);
	free(var_name);
	free(var_value);
	return (current);
}

char	*expand_variable(char *str, t_list *env, int *exit_status)
{
	int		i;
	char	*new_str;

	i = 0;
	if (!str || !env || !ft_strchr(str, '$'))
		return (NULL);
	new_str = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && !ft_strchr("\t $\'\"'\n'", str[i + 1])
			&& !is_heredoc_delim(str, i, exit_status))
		{
			if (!expand_status(&new_str, str[i + 1], exit_status, &i))
				continue ;
			i = expand_env_var(str, &new_str, i, env);
		}
		else
			new_str = ft_strjoin_char(new_str, str[i++]);
	}
	free(str);
	return (new_str);
}
