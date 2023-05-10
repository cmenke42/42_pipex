/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:08:33 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/10 19:12:44 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error_exit(char *error_text, int exit_code)
{
	if (exit_code != 0)
		perror(error_text);
	exit(exit_code);
}

char **ft_free_double_pointer(char **ptr)
{
	int i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
			free(ptr[i++]);
		free(ptr);
	}
	return (NULL);
}

void	ft_error_free_exit(char *error_text, char **envp_cmd_paths, int pipe_fds[2])
{
	int i;

	i = 0;
	perror(error_text);
	envp_cmd_paths = ft_free_double_pointer(envp_cmd_paths);
	if (pipe_fds[0] > 2)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
	}
	exit(1);
}


bool	ft_error_ret_false(char *error_text)
{
	perror(error_text);
	return (false);
}

char	*ft_get_cmd_path(char **envp_cmd_paths, char *cmd)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (envp_cmd_paths[i] && cmd)
	{
		cmd_path = ft_strjoin(envp_cmd_paths[i], cmd);
		if (!cmd_path)
		{
			i = 0;
			while(envp_cmd_paths[i])
				free(envp_cmd_paths[i++]);
			free(envp_cmd_paths);
			ft_error_exit("Malloc error cmd path", 1);
		}
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		else
			free(cmd_path);
		i++;
	}
	return (NULL);
}

//files_fd[0] = in;
//files_fd[1] = out;
void	ft_prepare_for_childs(int argc, char **argv, char **envp)
{
	char	**envp_cmd_paths;
	char	*cmd_line_1;
	char	*cmd_line_2;
	int		files_fd[2];
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	files_fd[0] = open(argv[1], O_RDONLY);
	if (files_fd[0] == -1)
		ft_error_ret_false("open error");
	files_fd[1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, mode);
	if (files_fd[1] == -1)
	{
		close(files_fd[0]);
		ft_error_ret_false("open error");
	}
	envp_cmd_paths = ft_get_envp_cmd_paths(envp);
	cmd_line_1 = ft_get_cmd_and_cmd_args(argv[2]);
	cmd_line_2 = ft_get_cmd_and_cmd_args(argv[3]);
}

// what to do with shell builtin commands especially when unset path is used -> nothing.
int	main(int argc, char **argv, char **envp)
{
	char	**envp_cmd_paths;
	int 	pipe_fds[2];
	pid_t	pid_first_child;
	pid_t	pid_last_child;
	int		stat_loc;
	int		return_status;

	if (argc != 5)
		return (1);
	envp_cmd_paths = ft_get_envp_cmd_paths(envp);
	if (pipe(pipe_fds) == -1)
		ft_error_free_exit("pipe eror", envp_cmd_paths, pipe_fds);
	//check for fork error
	pid_first_child = fork();
	if (pid_first_child == 0)
		ft_first_child(pipe_fds, argv, envp, envp_cmd_paths);
	else if (pid_first_child > 0)
		pid_last_child = fork();
	else
		ft_error_free_exit("fork error", envp_cmd_paths, pipe_fds);
	if (pid_last_child == 0)
		ft_last_child(pipe_fds, argv, envp, envp_cmd_paths);
	else if (pid_last_child == -1)
		ft_error_free_exit("fork error", envp_cmd_paths, pipe_fds);
	else
	{
		close(pipe_fds[1]);
		close(pipe_fds[0]);
		waitpid(pid_last_child, &stat_loc, WUNTRACED);
		if (WIFEXITED(stat_loc))
			return_status =  WEXITSTATUS(stat_loc);
		waitpid(pid_first_child, NULL, WUNTRACED);
		return (return_status);
	}
}