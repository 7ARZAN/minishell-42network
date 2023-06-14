/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:41:52 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/14 05:50:58 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*next_arg(char *cmd)
{
	int	i;

	i = 0;
	while (cmd && !ft_strchr(" \t|><", cmd[i]))
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			i = quote_len(cmd, i);
		i++;
	}
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
			i += next_arg(cmd + i) - cmd - i;
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
	args = ft_calloc(counter(cmd) + 1, sizeof(char *));
	while (cmd && cmd[i])
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

int	main(int ac, char **av)
{
	char	**args;
	int		i;

	i = 0;
	args = split_args(av[1]);
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
	return (0);
}
