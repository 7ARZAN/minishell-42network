/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:06:49 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/14 05:42:38 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_separator(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	wd_counts(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|' && is_quote(input[i]) == 0)
			count++;
		i++;
	}
	return (count + 1);
}

t_cmd	*split_cmd(char *input, int *error)
{
	int	i;
	t_cmd	*cmd;
	char	*tmp;

	i = 0;
	cmd = NULL;
	while (input[i])
	{
		tmp = ft_substr(input, i, wd_count(input));
		cmd = add_cmd(cmd, tmp, error);
	}
