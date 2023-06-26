/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 06:10:25 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/26 06:24:39 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	input_checker(char *input)
{
	int	i;
	char	*tmp;

	i = 0;
	if (input && input[i] == '.' && ft_strlen(input) == 1)
	{
		ft_putstr_fd("mish: .: filename argument required\n", 2);
		return (2);
	}
	if (input && input[i] == '~' && ft_strlen(input) == 1)
	{
		tmp = wd_replace("mish: ~: No such file or directory\n", "~", getenv("HOME"), 0);
		ft_putstr_fd(tmp, 2);
		free(tmp);
		return (126);
	}	
	if (input && input[i] == '/' && ft_strlen(input) == 1)
	{
		ft_putstr_fd("mish: /: No such file or directory\n", 2);
		return (126);
	}
	return (0);
}

void	ft_perror(char *cmd, char *path)
{
	int	*status;
	char	*tmp;

	status = malloc(sizeof(int));
	wait(status);
	if (WIFEXITED(*status))
	{
		if (WEXITSTATUS(*status) == 2)
			return ;
		if (WEXITSTATUS(*status) == 126)
		{
			tmp = wd_replace("mish: ", cmd, ": No such file or directory\n", 0);
			ft_putstr_fd(tmp, 2);
			free(tmp);
		}
		else if (WEXITSTATUS(*status) == 127)
		{
			tmp = wd_replace("mish: ", cmd, ": command not found\n", 0);
			ft_putstr_fd(tmp, 2);
			free(tmp);
		}
	}
	else if (WIFSIGNALED(*status))
	{
		if (WTERMSIG(*status) == 2)
			return ;
		if (WTERMSIG(*status) == 11)
		{
			tmp = wd_replace("mish: ", cmd, ": Segmentation fault\n", 0);
			ft_putstr_fd(tmp, 2);
			free(tmp);
		}
	}
	free(status);
}

