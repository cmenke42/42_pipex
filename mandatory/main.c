/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:08:33 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/24 02:00:46 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//mode sets the permissions of the file created if non existent.
//Permissions can be found in man 2 chmod.
// vars.files_fd[0] = in
// vars.files_fd[1] = out
void	ft_open_file_fds(char **argv, int files_fd[2])
{
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	files_fd[0] = open(argv[1], O_RDONLY);
	if (files_fd[0] == -1)
		perror("infile");
	files_fd[1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, mode);
	if (files_fd[1] == -1)
		perror("outfile");
}

//Gets the exit code of the second child process, this is the last command
//which has been executed
int	ft_child_exit_code(pid_t pid_child_1, pid_t pid_child_2)
{
	int	stat_loc;
	int	exit_code;

	exit_code = 0;
	waitpid(pid_child_2, &stat_loc, 0);
	if (WIFEXITED(stat_loc))
		exit_code = WEXITSTATUS(stat_loc);
	waitpid(pid_child_1, NULL, 0);
	return (exit_code);
}

int	ft_call_childs(char **envp_paths, t_vars *vars, char **envp, char **argv)
{
	pid_t	pid_child_1;
	pid_t	pid_child_2;

	if (pipe(vars->pipe_fds) == -1)
		ft_free_close_err_exit(vars->files_fd, NULL,
			envp_paths, "pipe - error");
	pid_child_1 = fork();
	if (pid_child_1 == -1)
	{
		ft_free_close_err_exit(vars->files_fd, vars->pipe_fds,
			envp_paths, "fork1 eror");
	}
	if (pid_child_1 == 0)
		ft_first_child(argv, envp_paths, vars, envp);
	pid_child_2 = fork();
	if (pid_child_2 == -1)
	{
		ft_free_close_err_exit(vars->files_fd, vars->pipe_fds,
			envp_paths, "fork2 eror");
	}
	if (pid_child_2 == 0)
		ft_last_child(argv, envp_paths, vars, envp);
	ft_close_fd(vars->files_fd, vars->pipe_fds);
	return (ft_child_exit_code(pid_child_1, pid_child_2));
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	int		exit_code;
	char	**envp_paths;

	if (argc != 5)
		exit(1);
	exit_code = 0;
	envp_paths = ft_get_envp_paths(envp);
	ft_open_file_fds(argv, vars.files_fd);
	exit_code = ft_call_childs(envp_paths, &vars, envp, argv);
	ft_free_double_pointer(envp_paths);
	return (exit_code);
}
