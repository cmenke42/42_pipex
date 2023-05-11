/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:52:02 by user              #+#    #+#             */
/*   Updated: 2023/05/11 16:25:58 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_first_child(int pipe_fds[2], t_vars vars, char **cmd_args, char *cmd)
{
	bool	no_error;
	
	no_error = true;
	if (no_error && dup2(vars.files_fd[0], STDIN_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	if (no_error && dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	ft_close_fd(vars.files_fd, pipe_fds);
	if (no_error && execve(cmd, cmd_args, vars.envp) == -1)
		perror("execve error");
	exit(1);
}


void	ft_last_child(int pipe_fds[2], t_vars vars, char **cmd_args, char *cmd)
{
	bool	no_error;
	
	no_error = true;
	if (no_error && dup2(vars.files_fd[1], STDOUT_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	if (no_error && dup2(pipe_fds[0], STDIN_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	ft_close_fd(vars.files_fd, pipe_fds);
	if (no_error && execve(cmd, cmd_args, vars.envp) == -1)
		perror("execve error - last child");
	exit(1);
}