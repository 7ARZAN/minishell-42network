/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:56:11 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/26 06:10:11 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*get_separator(char *str)
{
	int	i;
	int	index[3];
	char	*result;

	i = 0;
	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str && str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>')
			index[0] = i;
		else if (str[i] == '>' && str[i + 1] != '>')
			index[1] = i;
		else if (str[i] == '<')
			index[2] = i;
		i++;
	}
	{
	}
	return (result);
}

int	check_separator(t_cmd *cmd)
{
	char	*tmp;

	while (cmd && cmd->next)
	{
		tmp = get_separator(cmd->cmd);
		if (ft_strlen(tmp) == ft_strlen(cmd->cmd)
			|| (tmp[0] == '|' && ft_strlen(tmp) == 1))
		{
			ft_putstr_fd("mish: syntax error near unexpected token `|'\n", 2);
			free(tmp);
			return (1);
		}
		cmd->sep = ft_strdup(tmp);
		free(tmp);
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
