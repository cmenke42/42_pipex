/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:08:33 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/10 21:49:25 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//mode sets the permissions of the file created if non existent.
//Permissions can be found in man 2 chmod.
// files_fd[0] = in
// files_fd[1] = out
void	ft_open_file_fds(char **argv, int *files_fd)
{
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	files_fd[0] = open(argv[1], O_RDONLY);
	if (files_fd[0] == -1)
		perror("input - open error");
	files_fd[1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, mode);
	if (files_fd[1] == -1)
		perror("output - open error");
}

int	ft_create_childs(t_vars vars, int *files_fd, char **envp_paths)
{
	pid_t	child_1;
	pid_t	child_2;
	int		stat_loc;
	int		exit_code;
	int		pipe_fd[2];
	
	exit_code = 0;
	if (pipe(pipe_fd) == -1)
		ft_free_close_err_exit(files_fd, pipe_fd, envp_paths, "pipe error");
	child_1 = fork();
	if (child_1 > 0)
		ft_first_child(pipe_fd, files_fd[0], vars, envp_paths);
	else if(child_1 < 0)
		ft_free_close_err_exit(files_fd, pipe_fd, envp_paths, "fork 1 error");
	child_2 = fork();
	if (child_2 > 0)
		ft_last_child(pipe_fd, files_fd[1], vars, envp_paths);
	else if(child_2 < 0)
		ft_free_close_err_exit(files_fd, pipe_fd, envp_paths, "fork 2 error");
	ft_free_close_err_exit(files_fd, pipe_fd, envp_paths, NULL);
	waitpid(child_1, NULL, WUNTRACED);
	waitpid(child_2, &stat_loc, WUNTRACED);
	if (WIFEXITED(stat_loc))
		exit_code =  WEXITSTATUS(stat_loc);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	char	**envp_paths;
	t_vars	vars;
	int		files_fd[2];

	if (argc != 5)
		exit (1);
	vars.argv = argv;
	vars.envp = envp;
	envp_paths = ft_get_envp_cmd_paths(envp);
	ft_open_file_fds(argv, files_fd);
	return(ft_create_childs(vars, files_fd, envp_paths));	
}