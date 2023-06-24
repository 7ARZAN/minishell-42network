/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:56:11 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/24 17:16:48 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	print_error(char *str)
{
	ft_putstr_fd("Minishell: syntax error near unexpected token `|", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
}

static char	*get_separator(char *str)
{
	int	i[3];
	char	*res;
	
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (str[i[0]])
	{
		if (str[i[0]] == '\'' || str[i[0]] == '\"')
		{
			i[1] = i[0];
			i[0]++;
			while (str[i[0]] && str[i[0]] != str[i[1]])
				i[0]++;
		}
		if (str[i[0]] == '|')
			i[2]++;
		i[0]++;
	}
	if (i[2] == 0)
		return (ft_strdup(str));
	res = (char *)malloc(sizeof(char) * (i[0] + 1));
	i[0] = 0;
	i[1] = 0;
	while (str[i[0]])
	{
		if (str[i[0]] == '\'' || str[i[0]] == '\"')
		{
			i[1] = i[0];
			i[0]++;
			while (str[i[0]] && str[i[0]] != str[i[1]])
				i[0]++;
		}
		if (str[i[0]] == '|')
			break ;
		res[i[0]] = str[i[0]];
		i[0]++;
	}
	res[i[0]] = '\0';
	return (res);
}

int	check_separator(t_cmd *cmds)
{
	char	*tmp;

	while (cmds)
	{
		tmp = get_separator(cmds->cmd);
		if (ft_strlen(tmp) == ft_strlen(cmds->cmd)
			|| (tmp[0] == '|' && !cmds->next))
		{
			print_error(tmp);
			free(tmp);
			return (1);
		}
		free(tmp);
		cmds = cmds->next;
	}
	return (0);
}

int	main()
{
	char	*line;
	t_cmd	*cmds;
	int	i;

	i = 0;
	cmds = NULL;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			cmds = split_cmd(line);
			if (check_separator(cmds))
			{
				print_error("|");
				continue ;
			}
			while (cmds)
			{
				printf("cmd[%d] = %s\n", i, cmds->cmd);
				printf("args[%d] = %s\n", i, cmds->args[0]);
				cmds = cmds->next;
				i++;
			}
		}
		free(line);
	}
	return (0);
}
