/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:18:03 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/22 02:22:43 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*next_redi(char *cmd)
{
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	while (!ft_strchr("><", cmd[0]) || ((sq % 2) || (dq % 2)))
	{
		dq += (!(sq % 2) && cmd[0] == '\"');
		sq += (!(dq % 2) && cmd[0] == '\'');
		cmd++;
	}
	return (cmd);
}

static int	skip_spaces(char *cmd)
{
	int	count;

	count = 0;
	while (cmd[count] && ft_strchr("\t ", cmd[count]))
		count++;
	return (count);
}

static char	*extract_redirections(char *cmd)
{
	int	i;
	int	dquotes;
	int	squotes;

	i = 0;
	dquotes = 0;
	squotes = 0;
	if (ft_strchr("><", cmd[i]))
	{
		while (cmd[i] && ft_strchr("><", cmd[i]))
			i++;
		return (ft_substr(cmd, 0, i));
	}
	while (!ft_strchr("\t ><|", cmd[i]) || ((dquotes & 1) || (squotes & 1)))
	{
		dquotes += (!(squotes & 1) && cmd[i] == '"');
		squotes += (!(dquotes & 1) && cmd[i] == '\'');
		i++;
	}
	return (ft_substr(cmd, 0, i));
}

static int	redi_count(char *cmd)
{
	int	count;

	count = 0;
	cmd = next_redi(cmd);
	while (cmd[0])
	{
		count++;
		while (cmd[0] && ft_strchr("><", cmd[0]))
			cmd++;
		cmd = next_redi(cmd);
	}
	return (count);
}

char	**extract_redir(char *cmd)
{
	int		index;
	int		count;
	char	**result;

	index = 0;
	count = redi_count(cmd) * 2;
	result = ft_calloc(count + 2, sizeof(char *));
	result[index++] = ft_itoa(count);
	while (cmd && index < count)
	{
		cmd = next_redi(cmd);
		result[index] = extract_redirections(cmd);
		cmd += ft_strlen(result[index++]);
		cmd += skip_spaces(cmd);
		result[index++] = extract_redirections(cmd);
	}
	return (result);
}
