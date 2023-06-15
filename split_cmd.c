/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:06:49 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/15 09:04:15 by elakhfif         ###   ########.fr       */
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
		if (input[i] == '|')
			count++;
		i++;
	}
	return (count + 1);
}

t_cmd	*add_cmd(t_cmd *cmd, char *input, int *error)
{
	t_cmd	*new;
	t_cmd	*tmp;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = ft_strdup(input);
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
		tmp = ft_substr(input, i, ft_strlen(input));
		cmd = add_cmd(cmd, tmp, error);
	}
	return (cmd);
}

int	main(int ac, char **av)
{
	t_cmd	*cmd;
	int	error;

	error = 0;
	cmd = split_cmd(av[1], &error);
	if (error)
		printf("error\n");
	while (cmd)
	{
		printf("%s\n", cmd->cmd);
		cmd = cmd->next;
	}
	return (0);
}
