/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:37:11 by elakhfif          #+#    #+#             */
/*   Updated: 2023/07/03 19:40:51 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static int	wildcards_checker(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*' || str[i] == '?')
			return (1);
		i++;
	}
	return (0);
}

static void	wildcards_handler(char **str, char **tmp, int *i, int *j)
{
	char	*tmp2;

	tmp2 = NULL;
	if (wildcards_checker(*str))
	{
		tmp2 = ft_strdup(*str);
		*tmp = ft_strjoin(*tmp, ft_substr(*str, 0, *i));
		*tmp = ft_strjoin(*tmp, ft_substr(*str, *i + 1, ft_strlen(*str)));
		*str = ft_strdup(*tmp);
		*i = *i - 1;
		*j = *j - 1;
		free(tmp2);
	}
}

static char	*get_wildcards(char *str, int *i, int *j)
{
	char	*tmp;

	tmp = NULL;
	if (str[*i] == '*' && str[*i + 1] == '*')
	{
		tmp = ft_substr(str, 0, *i);
		tmp = ft_strjoin(tmp, ft_substr(str, *i + 1, ft_strlen(str)));
		*i = *i - 1;
		*j = *j - 1;
	}
	else if (str[*i] == '*' && str[*i + 1] == '?')
	{
		tmp = ft_substr(str, 0, *i);
		tmp = ft_strjoin(tmp, ft_substr(str, *i + 1, ft_strlen(str)));
		*i = *i - 1;
		*j = *j - 1;
	}
	else if (str[*i] == '?' && str[*i + 1] == '*')
	{
		tmp = ft_substr(str, 0, *i);
		tmp = ft_strjoin(tmp, ft_substr(str, *i + 1, ft_strlen(str)));
		*i = *i - 1;
		*j = *j - 1;
	}
	return (tmp);
}

char	*get_wildcards_str(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	while (str[i])
	{
		if (str[i] == '*' || str[i] == '?')
		{
			tmp = get_wildcards(str, &i, &j);
			if (tmp)
			{
				str = ft_strdup(tmp);
				free(tmp);
				tmp = NULL;
			}
		}
		i++;
		j++;
	}
	return (str);
}

int		wildcards(char **str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	while ((*str)[i])
	{
		if ((*str)[i] == '*' || (*str)[i] == '?')
		{
			tmp = get_wildcards(*str, &i, &j);
			if (tmp)
			{
				*str = ft_strdup(tmp);
				free(tmp);
				tmp = NULL;
			}
		}
		i++;
		j++;
	}
	return (0);
}

int main()
{
	char *str = ft_strdup("cat ?*");
	printf("%s\n", get_wildcards_str(str));
	return (0);
}
