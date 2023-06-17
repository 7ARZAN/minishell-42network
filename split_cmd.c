/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:06:49 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/18 00:16:18 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_quotes_loop(char *str)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !dq)
			sq = !sq;
		if (str[i] == '\"' && !sq)
			dq = !dq;
		i++;
	}
	return (sq || dq);
}

static int	check_quoted(t_cmd *cmd)
{
	while (cmd)
	{
		if (check_quotes_loop(cmd->cmd))
		{
			ft_putstr_fd("mish: Warning: quotes not closed\n", 2);
			return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}

static int	words_count(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|')
			count++;
		i++;
	}
	return (count + 1);
}

t_cmd	*add_cmd(t_cmd *cmd, char *input)
{
	t_cmd	*new;
	t_cmd	*tmp;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	new->cmd = input;
	new->next = NULL;
	if (!cmd)
		return (new);
	tmp = cmd;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (cmd);
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
		if (input[i] == '|')
		{
			tmp = ft_substr(input, 0, i);
			cmd = add_cmd(cmd, tmp);
			input = input + i + 1;
			i = 0;
		}
		i++;
	}
	cmd = add_cmd(cmd, input);
	if (check_quoted(cmd))
		*error = 1;
	return (cmd);
}

int	main(int ac, char **av)
{
	t_cmd	*cmd;
	int	error;

	error = 0;
	if (ac == 2)
	{
		cmd = split_cmd(av[1], &error);
		if (!error)
			printf("%s\n", cmd->cmd);
	}
	return (0);
}
