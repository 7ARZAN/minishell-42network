/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 09:52:20 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/26 04:45:30 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "parser.h"

static int	next_var(char *str, int index)
{
	int	i;
	int	dq;
	int	sq;

	i = index;
	dq = 0;
	sq = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !dq)
			sq = !sq;
		else if (str[i] == '\"' && !sq)
			dq = !dq;
		else if (str[i] == '$' && !dq && !sq)
			return (i);
		i++;
	}
	return (i);
}

static char	*get_var(char *str, int index)
{
	int		i;
	int		j;

	i = index + 1;
	j = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		i++;
		j++;
	}
	i += (str[i] == '?');
	return (ft_substr(str, index + 1, j));
}

static char	*skip_and_replace(char *str, char *fwd, char *swd, int index)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, 0, index);
	tmp2 = ft_strjoin(tmp, fwd);
	free(tmp);
	tmp = ft_strjoin(tmp2, str + index + ft_strlen(swd) + 1);
	free(tmp2);
	free(str);
	return (tmp);
}

static char	*clean_unused_var_symbols(char *str)
{
	int	i;
	int	dq;
	int	sq;

	i = 0;
	dq = 0;
	sq = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !dq)
			sq = !sq;
		else if (str[i] == '\"' && !sq)
			dq = !dq;
		else if (str[i] == '$' && !dq && !sq)
		{
			str[i] = '\0';
			return (str);
		}
		i++;
	}
	return (str);
}
// here im just adding the env struct to the function to get the value of the variable
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

static char	*get_env_value(char *var, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, var))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*is_escaped(char *str, int index)
{
	int	i;
	int	backslash;

	i = index - 1;
	backslash = 0;
	while (i >= 0 && str[i] == '\\')
	{
		backslash++;
		i--;
	}
	if (backslash % 2 == 0)
		return (NULL);
	return (str + i + 1);
}

char	*replace_var(char *str, t_env *env)
{
	int		i;
	char	*var;
	char	*value;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && !is_escaped(str, i))
		{
			var = get_var(str, i);
			value = get_env_value(var, env);
			if (value)
				str = skip_and_replace(str, value, var, i);
			else
				str = skip_and_replace(str, "", var, i);
			free(var);
			free(value);
		}
		i = next_var(str, i);
	}
	str = clean_unused_var_symbols(str);
	return (str);
}

int	main()
{
	int		i;
	char	*str;
	t_env	*env;

	i = 0;
	str = ft_strdup("hello $?, how are you $USER");
	env = malloc(sizeof(t_env));
	env->key = ft_strdup("USER");
	env->value = ft_strdup("elakhfif");
	env->next = NULL;
	str = replace_var(str, env);
	printf("%s\n", str);
	return (0);
}
