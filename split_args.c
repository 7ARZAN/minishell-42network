/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:41:52 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/13 15:50:43 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*next_arg(char *cmd)
{
	int	i;

	i = 0;
	while (!ft_strchr(" \t|><", cmd[i]) || is_quote(cmd[i] == 1))
		i++;
	return (cmd + i);
}

static int	counter(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (ft_strchr("><", cmd[i]))
		{
			while (ft_strchr("><", cmd[i]))
				i++;
			count--;
		}
		else if (!ft_strchr(" \t|", cmd[i]))
		{
			count++;
			//check next arg
		}
		else
			i++;
	}
	return (count);
}

char	**split_args(char *cmd)
{
	char	**args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	args = (char **)malloc(sizeof(char *) * (counter(cmd) + 1));
	while (cmd[i])
	{
		if (ft_strchr("><", cmd[i]))
		{
			while (ft_strchr("><", cmd[i]))
				i++;
			j--;
		}
		else if (!ft_strchr(" \t|", cmd[i]))
		{
			args[j] = ft_substr(cmd, i, next_arg(cmd + i) - cmd - i);
			i += next_arg(cmd + i) - cmd - i;
			j++;
		}
		else
			i++;
	}
	args[j] = NULL;
	return (args);
}
