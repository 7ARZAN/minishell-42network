/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:06:49 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/19 02:09:07 by elakhfif         ###   ########.fr       */
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
		if (!cmd->next)
			break ;
		else
			cmd = cmd->next;
	}
	return (0);
}

static int	words_count(char *input)
{

	int	count;
	int	sq;
	int	dq;

	count = 0;
	sq = 0;
	dq = 0;
	while (input && input[count])
	{
		if (input[count] == '\'' && !dq)
			sq = !sq;
		if (input[count] == '\"' && !sq)
			dq = !dq;
		if (input[count] == '|' && !sq && !dq)
			return (count);
		count++;
	}
	return (count);
}

t_cmd	*add_cmd(t_cmd *cmd, char *input)
{
	t_cmd	*new;
	t_cmd	*tmp;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
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

t_cmd	*input_split(char *input)
{
	t_cmd	*result;
	char	*temp;

	result = NULL;
	while (input[0])
	{
		temp = ft_substr(input, 0, words_count(input));
		result = add_cmd(result, temp);
		input = input + words_count(input);
		if (input[0] == '|')
			input++;
	}
	if (check_quoted(result))
		return (NULL);
	return (result);
}

// int	main(int ac, char **av)
// {
// 	t_cmd	*cmd;
// 	int	err;
//
// 	err = 0;
// 	if (ac == 2)
// 	{
// 		cmd = input_split(av[1]);
// 		while (cmd)
// 		{
// 			printf("%s\n", cmd->cmd);
// 			if (!cmd->next)
// 				break ;
// 			cmd = cmd->next;
// 		}
// 	}
// 	return (0);
// }
