/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:56:11 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/24 21:54:36 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*get_separator(char *str)
{
	int		index[3];
	char	*result;

	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[0])
	{
		if (index[1] % 2 == 0 && index[2] % 2 == 0)
		{
			if (str[0] == '|')
				result[index[0]++] = '|';
			else if (str[0] == '>' && str[1] == '>')
				result[index[0]++] = '>';
			else if (str[0] == '>' && str[1] != '>')
				result[index[0]++] = '>';
			else if (str[0] == '<' && str[1] == '<')
				result[index[0]++] = '<';
			else if (str[0] == '<' && str[1] != '<')
				result[index[0]++] = '<';
		}
		index[1] = (str[0] == '"') ? index[1] + 1 : index[1];
		index[2] = (str[0] == '\'') ? index[2] + 1 : index[2];
		str++;
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
