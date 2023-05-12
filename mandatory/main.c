/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:08:33 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/12 15:58:47 by cmenke           ###   ########.fr       */
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

// int	main(int argc, char **argv, char **envp)
// {
// 	char	**envp_paths;
// 	t_vars	vars;

// 	if (argc != 5)
// 		exit (1);
// 	vars.argv = argv;
// 	vars.envp = envp;
// 	envp_paths = ft_get_envp_paths(envp);
// 	ft_open_file_fds(vars);
// 	ft_create_childs(vars, envp_paths);
// 	exit (0);
// }

int ft_prepare_command(char *cmd_line, char **envp_paths)
{
	char	**splitted_cmd;
	char	*cmd_path;
	
	cmd_path = NULL;
	splitted_cmd = ft_get_cmd_line_elements(cmd_line);
	if (splitted_cmd)
		cmd_path = ft_get_cmd_path(envp_paths, splitted_cmd[0]);
	return (cmd_path);
}

int	main(int argc, char **argv, char **envp)
{
	char	**envp_paths;
	char	*cmd_path_1;
	char	*cmd_path_2;


	envp_paths = ft_get_envp_paths(envp);
	cmd_path_1 = ft_prepare_command(argv[2], envp_paths);
	cmd_path_2 = ft_prepare_command(argv[3], envp_paths);





	char **splitted_string;

	splitted_string = ft_get_cmd_line_elements(argv[1]);
	char **envp_paths = ft_get_envp_paths(envp);
	ft_print_double_pointer(splitted_string);
	char *cmd_path;

	cmd_path = ft_get_cmd_path(envp_paths, splitted_string[0]);
	ft_printf("cmd: %s\n", cmd_path);
}
