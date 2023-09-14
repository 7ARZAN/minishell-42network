/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 09:52:20 by elakhfif          #+#    #+#             */
/*   Updated: 2023/09/14 15:14:28 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*get_var_name(char *str, int i)
{
	char	*var_name;
	int		j;

	j = 0;
	var_name = (char *)malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		var_name[j] = str[j];
		j++;
	}
	var_name[j] = '\0';
	return (var_name);
}

static char	*skip_and_replace(char *str, char *wrd0, char *wrd1, int count)
{
	char	*tmp;
	char	*tmp1;
	char	*new_str;

	if (!str)
		return (NULL);
	tmp = ft_substr(str, 0, count);
	tmp1 = ft_substr(str, count + ft_strlen(wrd0), ft_strlen(str));
	new_str = ft_strjoin(tmp, wrd1);
	free(tmp);
	tmp = ft_strjoin(new_str, tmp1);
	free(new_str);
	free(tmp1);
	return (tmp);
}

static char	*clean_unused_var(char *str)
{
	int	i;
	int	dq;
	int	sq;

	i = 0;
	dq = 0;
	sq = 0;
	while (str[i])
	{
		if (str[i] == '\"' && !sq)
			dq = !dq;
		else if (str[i] == '\'' && !dq)
			sq = !sq;
		if (str[i] == '$' && !dq && !sq)
		{
			if (str[i + 1] == ' ' || str[i + 1] == '\0')
				str = skip_and_replace(str, "$", "", i);
		}
		i++;
	}
	return (str);
}

static int	get_var_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (1);
	while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"'
		&& str[i] != '$' && str[i] != '=' && str[i] != '/')
		i++;
	return (i);
}

static char	*get_var_value(char *var_name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, var_name))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

char		*expand_variable(char *str, t_env *env)
{
	int		i;
	char	*var_name;
	char	*var_value;

	i = 0;
	str = clean_unused_var(str);
	while (str[i])
	{
		if (str[i] == '$' && !ft_strchr("\'\"", str[i + 1]))
		{
			var_name = get_var_name(str + i + 1, get_var_len(str + i + 1));
			var_value = get_var_value(var_name, env);
			if (var_value)
				str = skip_and_replace(str, var_name, var_value, i + 1);
			else
				str = skip_and_replace(str, var_name, "", i + 1);
			free(var_name);
			free(var_value);
		}
		i++;
	}
	printf("var_name = %s\n", var_name);
	printf("var_value = %s\n", var_value);
	return (str);
}

int	main()
{
	printf("%s\n", expand_variable("echo $PATH", NULL));
}
