/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:13:04 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/19 23:29:27 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

enum e_redir
{
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
};

typedef struct	s_redir
{
	char	*redir_files;
	int	redir_type;
	struct s_redir	*next;
}				t_redir;

typedef struct	s_cmd
{
	char	*cmd;
	char	**args;
	t_redir	*redir;
	char	*sep;
	int	error;
	struct s_cmd	*next;
}				t_cmd;
//struct_cmd functions !
t_cmd	*add_cmd(t_cmd *cmd, char *input);

int	checker(t_cmd *cmd);

int	check_quotes(char *str);
int	skip_quotes(char *str, int i);
int	quote_closed(char *str, int i);
int	is_quote(char c);
int	quote_type(char c);
int	quote_len(char *str, int i);
int	remove_quotes(char *str);

#endif
