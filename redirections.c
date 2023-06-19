/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:17:38 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/19 04:08:14 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

enum e_redir
{
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
};

void	init_redir(t_redir *redir)
{
	redir->redir_files = NULL;
	redir->redir_type = 0;
}

static char	*extact_err_symbol(char *str)
{
	int	num;

	if(!str)
		return (NULL);
	num = 1;
	if (str[0] == str[1])
		num++;
	return (ft_substr(str, 0, num));
}

