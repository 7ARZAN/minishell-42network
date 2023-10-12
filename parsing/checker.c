/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:56:11 by elakhfif          #+#    #+#             */
/*   Updated: 2023/10/12 15:43:10 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	*check_syntax(char *input, int *status)
{
	int	i;

	i = 0;
	while (input && input[i] != '\0')
	{
		if (input[i] == '|')
		{
			i++;
			skip_wspaces(input, &i);
			if (input[i] == '|' || !input[i])
			{
				ft_putstr_fd("mish: syntax error\n", 2);
				*status = 1;
				return (NULL);
			}
		}
		i++;
	}
	return (status);
}
