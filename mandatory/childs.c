/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:52:02 by user              #+#    #+#             */
/*   Updated: 2023/05/11 01:39:40 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_first_child(int pipe_fds[2], int file_fd[2], t_vars vars, char **envp_paths)
{
	char	*cmd_path;
	char	**cmd_args;
	bool	no_error;
	
	cmd_path = NULL;
	no_error = true;
	cmd_args = ft_get_cmd_and_cmd_args(vars.argv[2]);
	if (cmd_args)
		cmd_path = ft_get_cmd_path(envp_paths, cmd_args[0]);
	if (no_error && dup2(file_fd[0], STDIN_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	if (no_error && dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	ft_close_fd(file_fd, pipe_fds);
	if (no_error && execve(cmd_path, cmd_args, vars.envp) == -1)
		perror("execve error");
	ft_free_double_pointer(envp_paths);
	if (cmd_path)
		free(cmd_path);
	exit(1);
}


void	ft_last_child(int pipe_fds[2], int file_fd[2], t_vars vars, char **envp_paths)
{
	char	*cmd_path;
	char	**cmd_args;
	bool	no_error;
	
	cmd_path = NULL;
	no_error = true;
	cmd_args = ft_get_cmd_and_cmd_args(vars.argv[3]);
	if (cmd_args)
		cmd_path = ft_get_cmd_path(envp_paths, cmd_args[0]);
	if (no_error && dup2(file_fd[1], STDOUT_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	if (no_error && dup2(pipe_fds[0], STDIN_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	ft_close_fd(file_fd, pipe_fds);
	if (no_error && execve(cmd_path, cmd_args, vars.envp) == -1)
		perror("execve error - last child");
	ft_free_double_pointer(envp_paths);
	if (cmd_path)
		free(cmd_path);
	exit(1);
}