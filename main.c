/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:43:33 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/22 06:08:53 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


int	main(void)
{
	char	*input;
	t_cmd	*cmds;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("\nexit\n");
			exit(0);
		}
		add_history(input);
		cmds = split_cmd(input);
		printf("cmd: %s\n", cmds->cmd);
		while (cmds->args++)
		{
			split_args(cmds->args[0]);
			printf("args: %s\n", cmds->args[0]);
		}
		cmds = cmds->next;
		free(input);
	}
	return (0);
}
