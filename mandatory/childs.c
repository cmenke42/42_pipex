/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:52:02 by user              #+#    #+#             */
/*   Updated: 2023/05/19 16:23:12 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_first_child(char **argv, char **envp_paths,
												t_vars *vars, char **envp)
{
	char	**splitted_cmd;
	char	*cmd_path;
	int		exit_code;

	exit_code = 0;
	splitted_cmd = NULL;
	cmd_path = ft_prepare_command(argv[2], &splitted_cmd, envp_paths);
	if (!cmd_path)
	{
		ft_putendl_fd("command not found", 2);
		exit_code = 127;
	}
	if (exit_code == 0 && vars->files_fd[0] == -1)
		exit_code = 1;
	if (exit_code == 0 && (dup2(vars->files_fd[0], STDIN_FILENO) == -1))
		exit_code = ft_error_ret_1("dup2 error");
	if (exit_code == 0 && dup2(vars->pipe_fds[1], STDOUT_FILENO) == -1)
		exit_code = ft_error_ret_1("dup2 error");
	ft_close_fd(vars->files_fd, vars->pipe_fds);
	if (exit_code == 0 && execve(cmd_path, splitted_cmd, envp) == -1)
		perror("execve error");
	ft_free_double_pointer(splitted_cmd);
	ft_close_standard_fd(STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
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
	cmd_path = ft_prepare_command(argv[3], &splitted_cmd, envp_paths);
	if (!cmd_path)
	{
		ft_putendl_fd("command not found-------", 2);
		exit_code = 127;
	}
	if (exit_code == 0 && vars->files_fd[1] == -1)
		exit_code = 1;
	if (exit_code == 0 && dup2(vars->files_fd[1], STDOUT_FILENO) == -1)
		exit_code = ft_error_ret_1("dup2 error");
	if (exit_code == 0 && dup2(vars->pipe_fds[0], STDIN_FILENO) == -1)
		exit_code = ft_error_ret_1("dup2 error");
	ft_close_fd(vars->files_fd, vars->pipe_fds);
	if (exit_code == 0 && execve(cmd_path, splitted_cmd, envp) == -1)
		perror("execve error - last child");
	ft_free_double_pointer(splitted_cmd);
	ft_close_standard_fd(STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
	free(cmd_path);
	exit(exit_code);
}
