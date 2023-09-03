/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:43:33 by elakhfif          #+#    #+#             */
/*   Updated: 2023/09/03 02:33:12 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


int	main(void)
{
	t_cmd	*cmds = NULL;
  	char	*input;
	int	i;

  	while (1)
	{
       		input = readline("minishell$ ");
		add_history(input);
		cmds = parser(input);
		while (cmds)
		{
			i = 0;
			printf("cmd = %s\n", cmds->cmd);
			while (cmds->args[i])
			{
				printf("args[%d] = %s\n", i, cmds->args[i]);
				i++;
			}
			cmds = cmds->next;
		}
		free(input);
		cmds = NULL;
	}
	return (0);
}

