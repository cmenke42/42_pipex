/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:08:33 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/16 16:52:30 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_print_double_pointer(char **str)
{
	int i;

	i = 0;
	while (str && str[i])
		ft_printf("%s\n", str[i++]);
}

void	ft_error_free_exit(char *error_text, char **envp_cmd_paths,
								int pipe_fds[2], int files_fd[2])
{
	perror(error_text);
	envp_cmd_paths = ft_free_double_pointer(envp_cmd_paths);
	ft_close_fd(files_fd, pipe_fds);
	exit(1);
}

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
		perror("input - open error");
	files_fd[1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, mode);
	if (files_fd[1] == -1)
		perror("output - open error");
}

char	*ft_prepare_command(char *cmd_line, char **envp_paths,
								char **splitted_cmd, char **envp)
{
	char	*cmd_path;

	cmd_path = NULL;
	envp_paths = NULL;
	envp_paths = ft_get_envp_paths(envp);
	splitted_cmd = ft_get_cmd_line_elements(cmd_line);
	if (splitted_cmd)
		cmd_path = ft_get_cmd_path(envp_paths, splitted_cmd[0]);
	ft_free_double_pointer(envp_paths);
	return (cmd_path);
}

int	ft_call_childs(char **envp_paths, int files_fd[2], t_vars *vars)
{
	pid_t	pid_child_1;	
	pid_t	pid_child_2;
	int		pipe_fds[2];
	int		exit_code;
	int		stat_loc;

	exit_code = 0;
	if (pipe(pipe_fds) == -1)
		ft_error_free_exit("pipe eror", envp_paths, pipe_fds, files_fd);
	pid_child_1 = fork();
	if (pid_child_1 == -1)
		ft_error_free_exit("fork eror", envp_paths, pipe_fds, files_fd);
	if (pid_child_1 == 0)
		ft_first_child(pipe_fds, files_fd, envp_paths, vars);
	pid_child_2 = fork();
	if (pid_child_2 == -1)
		ft_error_free_exit("fork eror", envp_paths, pipe_fds, files_fd);
	if (pid_child_2 == 0)
		ft_last_child(pipe_fds, files_fd, envp_paths, vars);
	// waitpid(pid_child_2, &stat_loc, WUNTRACED);
	// if (WIFEXITED(stat_loc))
	// 	exit_code =  WEXITSTATUS(stat_loc);
	// waitpid(pid_child_1, NULL, WUNTRACED);
	ft_close_fd(files_fd, pipe_fds);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	int		files_fd[2];
	int		exit_code;


	if (argc != 5)
		exit(1);
	exit_code = 0;
	vars.argv = argv;
	vars.envp = envp;
	ft_open_file_fds(argv, files_fd);
	exit_code = ft_call_childs(NULL, files_fd, &vars);
	return(exit_code);
}
