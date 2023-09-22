/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:56:11 by elakhfif          #+#    #+#             */
/*   Updated: 2023/09/22 23:39:10 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static char	*get_separator(char *str)
{
	int	i;
	char	*result;

	i = 0;
	result = (char *)ft_calloc(sizeof(char) , (ft_strlen(str) + 1));
	while (str && str[i])
	{
		if (ft_strchr("|", str[i]))
		{
			result[i] = str[i];
			return (result);
		}
		i++;
	}
	return (result);
}

int	check_separator(t_cmd *cmd)
{
	char	*tmp;

	while (cmd)
	{
		tmp = get_separator(cmd->cmd);
		ft_strtrim(tmp, " ");
		if (ft_strlen(tmp) == ft_strlen(cmd->cmd)
			|| (tmp[0] == '|' && ft_strlen(tmp) == 1))
		{
			ft_putstr_fd("mish: syntax error near unexpected token `|'\n", 2);
			free(tmp);
			return (1);
		}
		free(tmp);
		cmd = cmd->next;
	}
	return (0);
}

int	check_redirections(t_cmd *cmd)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (cmd)
	{
		while (cmd->cmd[i])
		{
			if (ft_strchr("><", cmd->cmd[i]))
				index++;
			i++;
		}
		if (index > 2 || (index == 2 && ft_strchr("><", cmd->cmd[0])) || (index == 2 && ft_strchr("><", cmd->cmd[ft_strlen(cmd->cmd) - 1])))
		{
			ft_putstr_fd("mish: syntax error near unexpected token `newline'\n", 2);
			return (1);
		}
		else if (index == 1 && ft_strchr("><", cmd->cmd[0]))
		{
			ft_putstr_fd("mish: syntax error near unexpected token `newline'\n", 2);
			return (1);
		}
		index = 0;
		i = 0;
		cmd = cmd->next;
	}
	return (0);
}

// int	main()
// {
// 	char	*line;
// 	t_cmd	*cmds;
//
// 	line = "hello | there | hey there > file | cat < file | cat > file";
// 	cmds = split_cmd(line);
// 	while (cmds)
// 	{
// 		if (check_separator(cmds) == 1)
// 			return (1);
// 		printf("cmd: %s\n", cmds->cmd);
// 		printf("sepator: %s\n", cmds->sep);
// 		cmds = cmds->next;
// 	}
// 	return (0);
// }
