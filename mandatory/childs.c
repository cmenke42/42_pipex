/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:52:02 by user              #+#    #+#             */
/*   Updated: 2023/05/10 21:49:33 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_first_child(int pipe_fds[2], int file_fd, t_vars vars, char **envp_paths)
{
	char	*cmd_path;
	char	**cmd_args;
	bool	no_error;
	
	cmd_path = NULL;
	no_error = true;
	cmd_args = ft_get_cmd_and_cmd_args(vars.argv[2]);
	if (cmd_args)
		cmd_path = ft_get_cmd_path(envp_paths, cmd_args[0]);
	if (no_error && dup2(file_fd, STDIN_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	if (no_error && dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	close(file_fd);
	close(pipe_fds[1]);
	close(pipe_fds[0]);
	if (no_error && execve(cmd_path, cmd_args, vars.envp) == -1)
		perror("execve error");
	exit(1);
}


void	ft_last_child(int pipe_fds[2], int file_fd, t_vars vars, char **envp_paths)
{
	char	*cmd_path;
	char	**cmd_args;
	bool	no_error;
	
	cmd_path = NULL;
	no_error = true;
	cmd_args = ft_get_cmd_and_cmd_args(vars.argv[3]);
	if (cmd_args)
		cmd_path = ft_get_cmd_path(envp_paths, cmd_args[0]);
	if (no_error && dup2(file_fd, STDOUT_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	if (no_error && dup2(pipe_fds[0], STDIN_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	close(file_fd);
	close(pipe_fds[1]);
	close(pipe_fds[0]);
	if (no_error && execve(cmd_path, cmd_args, vars.envp) == -1)
		perror("execve error - last child");
	exit(1);
}