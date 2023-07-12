/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:43:33 by elakhfif          #+#    #+#             */
/*   Updated: 2023/07/10 20:39:04 by elakhfif         ###   ########.fr       */
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
			while (cmds->args[i])
			{
				printf("args[%d] = %s\n", i, cmds->args[i]);
				i++;
			}
			printf("cmd = %s\n", cmds->cmd);
			printf("redirection file = %s\n", cmds->redir_files[0]);
			cmds = cmds->next;
		}
		cmds = NULL;
	}
}

