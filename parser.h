/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:13:04 by elakhfif          #+#    #+#             */
/*   Updated: 2023/06/23 05:18:56 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

enum e_redir
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	NONE
};

typedef struct	s_redir
{
	char	**redir_files;
	char	**redir_symbols;
	char	*heredoc;
}				t_redir;

typedef struct	s_cmd
{
	char	*cmd;
	char	**args;
	t_redir	*redir;
	char	*sep;
	int	error;
	//pid_t	process_id;
	struct s_cmd	*next;
}				t_cmd;

//split_cmd is a function that split the input into commands
t_cmd	*split_cmd(char *input);
//add_cmd is a function that add a command to the linked list
t_cmd	*add_cmd(t_cmd *cmd, char *input);
//main is a function that call the parser
int	main(void);
//split_args is a function that split the command into arguments
char	**split_args(char *cmd);
//parser is a function that parse the input and return a linked list of commands
t_cmd	*parser(char *line);

#endif
