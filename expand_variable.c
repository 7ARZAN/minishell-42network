/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 09:52:20 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/26 06:02:44 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*replace_var(char *str, t_env *env)
{
	int	i;
	char	*var;
	char	*tmp;
	char	*ret;

	ret = clean_unused_var_symbols(str);
	i = next_var(ret, 0);
	while (ret[i])
	{
		var = get_var(ret, i);
		tmp = all_wrds_replace(var, "$", NULL, 0);
		if (ft_strncmp("$?", var, 2) == 0)
			ret = skip_and_replace(ret, ft_itoa(EXIT_SUCCESS), var, i);
		else if (getenv(tmp))
			ret = skip_and_replace(ret, getenv(tmp), var, i);
		else
			ret = skip_and_replace(ret, "", var, i);
		i = next_var(ret, i);

	}
	return (ret);
}

// int	main()
// {
// 	int		i;
// 	char	*str;
// 	t_env	*env;
//
// 	i = 0;
// 	str = ft_strdup("hello $?, how are you $USER");
// 	env = malloc(sizeof(t_env));
// 	printf("%s\n", str);
// 	printf("%s\n", replace_var(str, env));
// 	return (0);
// }
