/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:08:33 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/11 16:52:55 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_free_and_ret(char **to_free, int ret_val)
{
	ft_free_double_pointer(to_free);
	return (ret_val);
}

int	ft_error_and_ret(char *error_text, int ret_val)
{
	perror(error_text);
	return (ret_val);
}

//mode sets the permissions of the file created if non existent.
//Permissions can be found in man 2 chmod.
// vars.files_fd[0] = in
// vars.files_fd[1] = out
void	ft_open_file_fds(t_vars vars)
{
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	vars.files_fd[0] = open(vars.argv[1], O_RDONLY);
	if (vars.files_fd[0] == -1)
		perror("input - open error");
	vars.files_fd[1] = open(vars.argv[4], O_WRONLY | O_TRUNC | O_CREAT, mode);
	if (vars.files_fd[1] == -1)
		perror("output - open error");
}

char **ft_cmd_path_for_child(t_vars vars, char **envp_paths, int *exit_code, char *cmd_path)
{
	char	**cmd_args;

	cmd_args = NULL;
	cmd_path = NULL;
	cmd_args = ft_get_cmd_and_cmd_args(vars.argv[2]);
	if (cmd_args)
		cmd_path = ft_get_cmd_path(envp_paths, cmd_args[0]);
	if (!cmd_path)
	{
		free(cmd_args);
		ft_putendl_fd("command not found", 2);
		*exit_code = 127;
	}
	return (cmd_args);
}

int	ft_create_child_1(t_vars vars, char **envp_paths, int *pipe_fd, pid_t *child_1)
{
	int		exit_code;
	char	*cmd_path;
	char	**cmd_args;
	
	if (vars.files_fd[0] < 0)
		return (1);
	exit_code = 0;
	cmd_path = NULL;
	cmd_args = ft_cmd_path_for_child(vars, envp_paths, &exit_code, cmd_path);
	if (!cmd_path)
		return (ft_free_and_ret(cmd_args, exit_code));
	*child_1 = fork();
	if (*child_1 == 0)
		ft_first_child(pipe_fd, vars, cmd_args, cmd_path);
	else if(*child_1 < 0)
		exit_code = ft_error_and_ret("fork 1 failed", 1);
	free(cmd_path);
	return (exit_code);
}

int	ft_create_child_2(t_vars vars, char **envp_paths, int *pipe_fd, pid_t *child_2)
{
	int		exit_code;
	char	*cmd_path;
	char	**cmd_args;
	
	if (vars.files_fd[1] < 0)
		return (1);
	exit_code = 0;
	cmd_path = NULL;
	cmd_args = ft_cmd_path_for_child(vars, envp_paths, &exit_code, cmd_path);
	if (!cmd_path)
		return (ft_free_and_ret(cmd_args, exit_code));
	*child_2 = fork();
	if (*child_2 == 0)
		ft_last_child(pipe_fd, vars, cmd_args, cmd_path);
	else if(*child_2 < 0)
		exit_code = ft_error_and_ret("fork 1 failed", 1);
	free(cmd_path);
	return (exit_code);
}

int	ft_create_childs(t_vars vars, char **envp_paths)
{
	int		exit_code;
	int		pipe_fd[2];
	pid_t	child_1;
	pid_t	child_2;
	int		stat_loc;
	
	exit_code = 0;
	child_1 = 0;
	child_2 = 0;
	if (pipe(pipe_fd) == -1)
		ft_free_close_err_exit(vars.files_fd, pipe_fd, envp_paths, "pipe error");
	ft_create_child_1(vars, envp_paths, pipe_fd, &child_1);
	exit_code = ft_create_child_2(vars, envp_paths, pipe_fd, &child_2);
	waitpid(child_2, &stat_loc, WUNTRACED);
	if (WIFEXITED(stat_loc))
		exit_code =  WEXITSTATUS(stat_loc);
	waitpid(child_1, NULL, WUNTRACED);
	ft_free_close_err_exit(vars.files_fd, pipe_fd, envp_paths, NULL);
	exit(exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	char	**envp_paths;
	t_vars	vars;

	if (argc != 5)
		exit (1);
	vars.argv = argv;
	vars.envp = envp;
	envp_paths = ft_get_envp_paths(envp);
	ft_open_file_fds(vars);
	ft_create_childs(vars, envp_paths);
	exit (0);
}

	// int i;

	// i = 0;
	// if (envp_paths)
	// {
	// 	while (envp_paths[i])
	// 		ft_printf("%s\n", envp_paths[i++]);
	// }