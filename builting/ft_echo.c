/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:19:21 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/09/23 23:06:25 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builting.h"

int	ft_echo(char **args)
{
	int	flag;

	flag = 0;
	args++;
	while (*args && !ft_strcmp(*args, "-n"))
	{
		args++;
		flag = 1;
	}
	while (*args)
	{
		ft_putstr_fd(*args, STDOUT_FILENO);
		args++;
		if (*args)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	ft_echo(av);
// 	return (0);
// }
