/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:52:02 by user              #+#    #+#             */
/*   Updated: 2023/05/16 16:56:43 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_first_child(int pipe_fds[2], int files_fd[2], char **envp_paths,
												t_vars *vars)
{
	bool	no_error;
	char	**splitted_cmd;
	char	*cmd_path;

	no_error = true;
	splitted_cmd = NULL;
	cmd_path = ft_prepare_command(vars->argv[2], envp_paths, splitted_cmd, vars->envp);
	if (!cmd_path)
	{
		ft_putendl_fd("command not found", 2);
		ft_free_double_pointer(splitted_cmd);
		exit(127);
	}
	ft_print_double_pointer(splitted_cmd);
	if (no_error && dup2(files_fd[0], STDIN_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	if (no_error && dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	ft_close_fd(files_fd, pipe_fds);
	if (no_error && execve(cmd_path, splitted_cmd, NULL) == -1)
		perror("execve error");
	ft_free_double_pointer(splitted_cmd);
	if (cmd_path)
		free(cmd_path);
	exit(1);
}


void	ft_last_child(int pipe_fds[2], int files_fd[2], char **envp_paths,
												t_vars *vars)
{
	bool	no_error;
	char	**splitted_cmd;
	char	*cmd_path;

	no_error = true;
	splitted_cmd = NULL;
	cmd_path = ft_prepare_command(vars->argv[3], envp_paths, splitted_cmd, vars->envp);
	if (!cmd_path)
	{
		ft_putendl_fd("command not found", 2);
		ft_free_double_pointer(splitted_cmd);
		exit(127);
	}
	if (no_error && dup2(files_fd[1], STDOUT_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	if (no_error && dup2(pipe_fds[0], STDIN_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	ft_close_fd(files_fd, pipe_fds);
	if (no_error && execve(cmd_path, splitted_cmd, NULL) == -1)
		perror("execve error - last child");
	ft_free_double_pointer(splitted_cmd);
	if (cmd_path)
		free(cmd_path);
	exit(1);
}

// void	ft_first_child(int pipe_fds[2], t_vars vars, char **cmd_args, char *cmd)
// {
// 	bool	no_error;
	
// 	no_error = true;
// 	if (no_error && dup2(vars.files_fd[0], STDIN_FILENO) == -1)
// 		no_error = ft_error_ret_false("dup2 error");
// 	if (no_error && dup2(pipe_fds[1], STDOUT_FILENO) == -1)
// 		no_error = ft_error_ret_false("dup2 error");
// 	ft_close_fd(vars.files_fd, pipe_fds);
// 	if (no_error && execve(cmd, cmd_args, vars.envp) == -1)
// 		perror("execve error");
// 	exit(1);
// }


// void	ft_last_child(int pipe_fds[2], t_vars vars, char **cmd_args, char *cmd)
// {
// 	bool	no_error;
	
// 	no_error = true;
// 	if (no_error && dup2(vars.files_fd[1], STDOUT_FILENO) == -1)
// 		no_error = ft_error_ret_false("dup2 error");
// 	if (no_error && dup2(pipe_fds[0], STDIN_FILENO) == -1)
// 		no_error = ft_error_ret_false("dup2 error");
// 	ft_close_fd(vars.files_fd, pipe_fds);
// 	if (no_error && execve(cmd, cmd_args, vars.envp) == -1)
// 		perror("execve error - last child");
// 	exit(1);
// }