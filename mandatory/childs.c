/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:24:49 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/24 18:31:37 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//closing all fds since they are copied from the parent process.
//freeing all the thigns allocated in the main in case of an error from execve
//otherwise execve takes care of it.
void	ft_first_child(char **argv, char **envp_paths,
												t_vars *vars, char **envp)
{
	char	**splitted_cmd;
	char	*cmd_path;
	int		exit_code;

	exit_code = 0;
	splitted_cmd = NULL;
	cmd_path = NULL;
	if (vars->files_fd[0] != -1)
		cmd_path = ft_prepare_command(argv[2], &splitted_cmd, envp_paths);
	else
		exit_code = 1;
	if (exit_code == 0 && !cmd_path)
		exit_code = ft_error_ret_exit_code("command not found", 127);
	if (exit_code == 0 && (dup2(vars->files_fd[0], STDIN_FILENO) == -1))
		exit_code = ft_error_ret_exit_code("dup2 error", 1);
	if (exit_code == 0 && dup2(vars->pipe_fds[1], STDOUT_FILENO) == -1)
		exit_code = ft_error_ret_exit_code("dup2 error", 1);
	ft_close_fd(vars->files_fd, vars->pipe_fds);
	ft_free_double_pointer(envp_paths);
	if (exit_code == 0 && execve(cmd_path, splitted_cmd, envp) == -1)
		perror("execve error");
	ft_free_double_pointer(splitted_cmd);
	ft_close_standard_fd();
	free(cmd_path);
	exit(exit_code);
}

void	ft_last_child(char **argv, char **envp_paths,
												t_vars *vars, char **envp)
{
	int		exit_code;
	char	**splitted_cmd;
	char	*cmd_path;

	exit_code = 0;
	splitted_cmd = NULL;
	cmd_path = NULL;
	if (vars->files_fd[1] != -1)
		cmd_path = ft_prepare_command(argv[3], &splitted_cmd, envp_paths);
	else
		exit_code = 1;
	if (exit_code == 0 && !cmd_path)
		exit_code = ft_error_ret_exit_code("command not found", 127);
	if (exit_code == 0 && dup2(vars->files_fd[1], STDOUT_FILENO) == -1)
		exit_code = ft_error_ret_exit_code("dup2 error", 1);
	if (exit_code == 0 && dup2(vars->pipe_fds[0], STDIN_FILENO) == -1)
		exit_code = ft_error_ret_exit_code("dup2 error", 1);
	ft_close_fd(vars->files_fd, vars->pipe_fds);
	ft_free_double_pointer(envp_paths);
	if (exit_code == 0 && execve(cmd_path, splitted_cmd, envp) == -1)
		perror("execve error - last child");
	ft_free_double_pointer(splitted_cmd);
	ft_close_standard_fd();
	free(cmd_path);
	exit(exit_code);
}
