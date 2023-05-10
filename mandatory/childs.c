/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:52:02 by user              #+#    #+#             */
/*   Updated: 2023/05/10 19:02:58 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_first_child(int pipe_fds[2], char **argv, char **envp, char **envp_cmd_paths)
{
	int		infile_fd;
	char	*cmd_path;
	char	**cmd_args;
	bool	no_error;
	
	cmd_path = NULL;
	cmd_args = ft_get_cmd_and_cmd_args(argv[2]);

	if (cmd_args)
		cmd_path = ft_get_cmd_path(envp_cmd_paths, cmd_args[0]);
	no_error = true;
	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
		no_error = ft_error_ret_false("open error");
	if (no_error && dup2(infile_fd, STDIN_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	if (no_error && dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	if (infile_fd != -1)
		close(infile_fd);
	close(pipe_fds[1]);
	close(pipe_fds[0]);
	if (no_error && execve(cmd_path, cmd_args, envp) == -1)
		perror("execve error");
	exit(1);
}

//mode sets the permissions of the file created if non existent.
//Permissions can be found in man 2 chmod.
void	ft_last_child(int pipe_fds[2], char **argv, char **envp, char **envp_cmd_paths)
{
	int		outfile_fd;
	mode_t	mode;
	char	*cmd_path;
	char	**cmd_args;
	bool	no_error;
	
	cmd_path = NULL;
	cmd_args = ft_get_cmd_and_cmd_args(argv[3]);
	if (cmd_args)
		cmd_path = ft_get_cmd_path(envp_cmd_paths, cmd_args[0]);
	no_error = true;
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	outfile_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, mode);
	if (outfile_fd == -1)
		no_error = ft_error_ret_false("open error");
	if (no_error && dup2(outfile_fd, STDOUT_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	if (no_error && dup2(pipe_fds[0], STDIN_FILENO) == -1)
		no_error = ft_error_ret_false("dup2 error");
	if (outfile_fd != -1)
		close(outfile_fd);
	close(pipe_fds[1]);
	close(pipe_fds[0]);
	if (no_error && execve(cmd_path, cmd_args, envp) == -1)
		perror("execve error - last child");
	exit(1);
}