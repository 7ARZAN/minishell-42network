/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:31:05 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/09/09 08:22:08 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builting.h"


static int	check_the_number(char *str)
{
  if (!str)
    return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

int ft_exit(char **args)
{
	if (args[1] && args[2])
	{
		ft_error("exit", "too many arguments");
		return (1);
	}
	if (check_the_number(args[1]))
		exit(255);
	if (args[1])
		exit(ft_atoi(args[1]));
  exit(0);
  return (0);
}

// int main(int argc, char **argv)
// {
// 	ft_exit(argv);
// 	return (0);
// }