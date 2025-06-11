/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr <yel-hadr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:15:09 by elakhfif          #+#    #+#             */
/*   Updated: 2023/10/12 05:31:09 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

char	*remove_quotes(char *cmd)
{
	int		i;
	int		dq;
	int		sq;
	char	*res;

	i = 0;
	dq = 0;
	sq = 0;
	res = ft_calloc(ft_strlen(cmd) + 1, sizeof(char));
	if (!cmd)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] == '\'' && !dq)
			sq = !sq;
		else if (cmd[i] == '\"' && !sq)
			dq = !dq;
		else
			res = ft_strjoin_char(res, cmd[i]);
		i++;
	}
	return (res);
}

// int	main(void)
// {
// 	char	*cmd;
// 	char	*res;
//
// 	cmd = ft_strdup("echo \"hello world\"");
// 	res = remove_quotes(cmd);
// 	printf("%s\n", res);
// 	return (0);
// }
