/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:41:52 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/18 03:25:39 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*next_arg(char *cmd)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (cmd && !ft_strchr(" \t><", cmd[i]))
	{
		if (cmd[i] == '\'' && !dq)
			sq = !sq;
		else if (cmd[i] == '\"' && !sq)
			dq = !dq;
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
	while (cmd && cmd[i])
	{
		while (cmd[i] && ft_strchr(" \t", cmd[i]))
			i++;
		if (cmd[i] && !ft_strchr("><", cmd[i]))
		{
			count++;
			i += next_arg(cmd + i) - cmd - i;
		}
		else
			i++;
	}
	return (count + 1);
}

char	**split_args(char *cmd)
{
	char	**args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	args = ft_calloc(counter(cmd), sizeof(char *));
	while (cmd && cmd[i])
	{
}

int	main(int ac, char **av)
{
	char	**args;
	int		i;

	i = 0;
	args = split_args(av[1]);
	while (args[i])
	{
		printf("here is the arg [%d]:\t\"%s\"\n", i, args[i]);
		i++;
	}
	return (0);
}
