/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:56:11 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/16 11:05:10 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	ft_perror(char *str)
{
	ft_putstr_fd("mish: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
}

static char	*take_sep(char *str)
{
	int	i;
	int	j;
	char	*sep;

	i = 0;
	j = 0;
	sep = (char *)malloc(sizeof(char) * 3);
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
	{
		sep[j] = str[i];
		i++;
		j++;
	}
	sep[j] = '\0';
	return (sep);
}

int	checker(char *str)
{
	int	i;
	char	*sep;

	i = 0;
	while (str && str[i])
	{
		sep = take_sep(str + i);
		if (!ft_strcmp(sep, ">>") || !ft_strcmp(sep, "<<") || !ft_strcmp(sep, ">") || !ft_strcmp(sep, "<") || !ft_strcmp(sep, "|"))
			return (1);
		i += ft_strlen(sep);
		free(sep);
	}
	return (0);
}

int main(int ac, char **av)
{
	int	fd;
	char	*line;
	char	*str;
	int	i;

	i = 0;
	if (ac == 1)
	{
		while (1)
		{
			read(0, &line, 1);
			if (!line)
				break ;
			str = ft_strjoin(str, line);
			free(line);
		}
		if (checker(str))
			ft_perror("syntax error near unexpected token\n");
	}
	else if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			ft_perror("No such file or directory\n");
		while (read(fd, &line, 1))
		{
			str = ft_strjoin(str, line);
			free(line);
		}
		if (checker(str))
			ft_perror("syntax error near unexpected token\n");
	}
	else
		ft_perror("Too many arguments\n");
	return (0);
}
