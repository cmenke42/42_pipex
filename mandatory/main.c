/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:08:33 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/16 19:20:45 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_print_double_pointer(char **str)
{
	int	i;

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

char	*ft_prepare_command(char *cmd_line, char ***splitted_cmd,
								char **envp_paths)
{
	char	*cmd_path;

	cmd_path = NULL;
	*splitted_cmd = ft_get_cmd_line_elements(cmd_line);
	if (splitted_cmd)
		cmd_path = ft_get_cmd_path(envp_paths, *splitted_cmd[0]);
	ft_free_double_pointer(envp_paths);
	return (cmd_path);
}

int	ft_child_exit_code(pid_t pid_child_1, pid_t pid_child_2)
{
	int	stat_loc;
	int	exit_code;

	exit_code = 0;
	waitpid(pid_child_2, &stat_loc, WUNTRACED);
	if (WIFEXITED(stat_loc))
		exit_code = WEXITSTATUS(stat_loc);
	waitpid(pid_child_1, NULL, WUNTRACED);
	return (exit_code);
}

int	ft_call_childs(char **envp_paths, t_vars *vars, char **envp, char **argv)
{
	pid_t	pid_child_1;	
	pid_t	pid_child_2;

	if (pipe(vars->pipe_fds) == -1)
		ft_error_free_exit("pipe - error", envp_paths,
			vars->pipe_fds, vars->files_fd);
	pid_child_1 = fork();
	if (pid_child_1 == -1)
		ft_error_free_exit("fork eror", envp_paths,
			vars->pipe_fds, vars->files_fd);
	if (pid_child_1 == 0)
		ft_first_child(argv, envp_paths, vars, envp);
	close(vars->pipe_fds[1]);
	pid_child_2 = fork();
	if (pid_child_2 == -1)
		ft_error_free_exit("fork eror", envp_paths,
			vars->pipe_fds, vars->files_fd);
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
