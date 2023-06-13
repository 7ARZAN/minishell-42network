/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:13:04 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/13 18:26:39 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_cmd
{
	char	*cmd;
	char	**args;
	char	**redir_files;
	char	**redir_type;
	char	*del;
	int	error;
	struct s_cmd	*next;
}				t_cmd;


int	check_quotes(char *str);
int	skip_quotes(char *str, int i);
int	quote_closed(char *str, int i);
int	is_quote(char c);
int	quote_type(char c);
int	quote_len(char *str, int i);

#endif
