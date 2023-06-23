/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:43:33 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/23 06:04:59 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


int	main(void)
{
	t_cmd	*cmds;
  	char	*input;
	int	i;

  	while (1)
	{
       		input = readline("minishell$ ");
		add_history(input);
		cmds = parser(input);
		while (cmds)
		{
			printf("cmd is:\t\t%s\n", cmds->cmd);
			i = 0;
			while (cmds->args[i])
			{
				printf("args is:\t%s\n", cmds->args[i]);
				i++;
			}
			cmds = cmds->next;
		}
	}
	return (0);
}

