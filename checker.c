/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:56:11 by elakhfif          #+#    #+#             */
/*   Updated: 2023/09/04 02:24:09 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*get_separator(char *str)
{
	char	*tmp;
	int	indx[3];

	indx[0] = 0;
	indx[1] = 0;
	indx[2] = 0;
	tmp = ft_strdup(str);
	while (str[indx[0]])
	{
		if (ft_strchr("\'\"", str[indx[0]]))
			indx[2] = str[indx[0]];
		if (str[indx[0]] == '|' && !indx[2])
			tmp[indx[1]++] = '|';
		indx[0]++;
	}
	tmp[indx[1]] = '\0';
	return (tmp);
}

int	check_separator(t_cmd *cmd)
{
	char	*tmp;

	while (cmd)
	{
		tmp = get_separator(cmd->cmd);
		if (ft_strlen(tmp) != 0)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(tmp, 2);
			ft_putstr_fd("'\n", 2);
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
