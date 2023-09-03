/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 08:51:51 by elakhfif          #+#    #+#             */
/*   Updated: 2023/07/26 08:57:50 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	next_variable(char *str, int index)
{
	int	i;
	int	sq;
	int	dq;

	i = index;
	sq = 0;
	dq = 0;
	while (str[i])
	{
		sq += (str[i] == '\'');
		dq += (str[i] == '"');
		if (str[i] == '$' && !(sq & 1) && !(dq & 1))
			return (i);
		i++;
	}
	return (-1);
}

static char	*get_variable_name(char *str, int index)
{
	int	i;

	i = index + 1;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')
			|| str[i] == '_'))
		i++;
	i += (str[i] == '?');
	return (ft_substr(str, index, i - index));
}

static char	*skip_and_replace(char *str, char *w0, char *w1, int count)
{
	char	*result;
	char	*temp;
	int	i;
	int	j;

	i = -1;
	j = 0;
	result = malloc(ft_strlen(str) - ft_strlen(w0) + ft_strlen(w1) + 1);
	while (++i < count)
		result[i] = str[i];
	while (w1 && w1[j])
		result[i++] = w1[j++];
	j = -1;
	while (str[++i + ft_strlen(w0) - 1])
		result[i] = str[i + ft_strlen(w0) - 1];
	result[i] = '\0';
	free(str);
	free(w0);
	return (result);
}

static char	*clean_unused_var_sym(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			str[j] = str[i];
			j++;
			i++;
			while (str[i] && str[i] != str[j - 1])
			{
				str[j] = str[i];
				j++;
				i++;
			}
		}
		else
		{
			str[j] = str[i];
			j++;
			i++;
		}
	}
	str[j] = '\0';
	return (str);
}

char	*replace_variables(char *str, int err)
{
	int		var_index;
	char	*var_name;
	char	*temp;
	char	*result;

	result = clean_unused_var_sym(ft_strdup(str));
	var_index = next_variable(result, 0);
	while (var_index != -1)
	{
		var_name = get_variable_name(result, var_index);
		temp = ft_strdup(var_name);
		if (ft_strncmp("$?", var_name, 3))
			result = skip_and_replace(result, var_name, getenv(temp), var_index);
		else
		{
			free(temp);
			temp = ft_itoa(err);
			result = skip_and_replace(result, var_name, temp, var_index);
		}
		free(temp);
		var_index = next_variable(result, 0);
	}
	return (result);
}

// int	main(void)
// {
// 	char	*str;
// 	int		err;
//
// 	err = 0;
// 	str = ft_strdup("echo $?$HOBME");
// 	printf("%s\n", replace_variables(str, err));
// 	return (0);
// }
