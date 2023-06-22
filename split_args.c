/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:41:52 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/22 05:55:23 by elakhfif         ###   ########.fr       */
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
	while (cmd[i] && (cmd[i] != ' ' || sq || dq))
	{
		if (cmd[i] == '\'' && !dq)
			sq = !sq;
		else if (cmd[i] == '\"' && !sq)
			dq = !dq;
		i++;
	}
	return (cmd + i);
}

static int	args_count(char *cmd)
{
	int	count;

	count = 0;
	while (cmd[0])
	{
		if (ft_strchr("><", cmd[0]))
		{
			while (ft_strchr("><", cmd[0]))
				cmd++;
			count--;
		}
		else if (!ft_strchr("\t |;", cmd[0]))
		{
			count++;
			cmd = next_arg(cmd);
		}
		else
			cmd++;
	}
	return (count);
}

char	**split_args(char *cmd)
{
	int		index;
	int		count;
	char	*tmp;
	char	**result;

	index = 0;
	count = args_count(cmd);
	result = ft_calloc(count + 1, sizeof(char *));
	while (index < count)
	{
		while (cmd[0] && ft_strchr("\t ", cmd[0]))
			cmd++;
		if (ft_strchr("><", cmd[0]))
			while (ft_strchr("\t ><", cmd[0]))
				cmd++;
		else
		{
			tmp = ft_substr(cmd, 0,
					(ft_strlen(cmd) - ft_strlen(next_arg(cmd))));
			result[index++] = tmp;
		}
		cmd = next_arg(cmd);
	}
	result[index] = NULL;
	return (result);
}

// int	main(int ac, char **av)
// {
// 	char	**args;
// 	int		i;
//
// 	i = 0;
// 	args = split_args(av[1]);
// 	printf("here is the cmd:\t\"%s\"\n", av[1]);
// 	while (args[i] != NULL)
// 	{
// 		printf("here is the arg [%d]:\t\"%s\"\n", i, args[i]);
// 		i++;
// 	}
// 	return (0);
// }
