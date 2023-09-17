/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_the_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:34:40 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/09/16 08:48:32 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"


// int ft_herdoc(t_execute *cmd)
// {
// 	if (cmd->cmd->redir_in.redir == REDIR_HEREDOC)
// 	{
// 		pipe(cmd->herdoc_fd);
// 		write(cmd->herdoc_fd[1], cmd->cmd->redir_in.file, ft_strlen(cmd->cmd->redir_in.file));
// 		close(cmd->herdoc_fd[1]);
// 		dup2(cmd->herdoc_fd[0], STDIN_FILENO);
// 		close(cmd->herdoc_fd[0]);
// 	}
// 	return (0);
// }

void ft_save_fd(int *save_stdin, int *save_stdout)
{
  *save_stdin = dup(STDIN_FILENO);
  *save_stdout = dup(STDOUT_FILENO);
}

void ft_restore_fd(int save_stdin, int save_stdout)
{
  dup2(save_stdin, STDIN_FILENO);
  dup2(save_stdout, STDOUT_FILENO);
  close(save_stdin);
  close(save_stdout);
}

int ft_execute(t_cmd *cmd, t_list *envp)
{
	char **env;
	env = ft_lst_to_char(envp);
	if (ft_redaraction(cmd->redir_in.file, cmd->redir_in.type) == -1)
		return (1);
	if (ft_redaraction(cmd->redir_out.file, cmd->redir_out.type) == -1)
		return (1);
	if (cmd->args[0])
		execve(cmd->args[0], cmd->args, env);
	return (1);
}