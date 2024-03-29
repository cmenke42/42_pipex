/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_and_cmd_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:14:18 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/24 17:48:25 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_add_slash_to_envp_paths(char **envp_paths)
{
	char	**result;
	int		i;

	i = 0;
	while (envp_paths && envp_paths[i])
		i++;
	result = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!result)
		perror("Malloc error add slash");
	i = 0;
	while (envp_paths && envp_paths[i])
	{
		result[i] = ft_strjoin(envp_paths[i], "/");
		if (!result[i])
		{
			perror("Malloc error join slash");
			result = ft_free_double_pointer(result);
			break ;
		}
		i++;
	}
	ft_free_double_pointer(envp_paths);
	return (result);
}

char	**ft_get_envp_paths(char **envp)
{
	int		i;
	char	*path_string;
	char	**envp_paths;

	i = 0;
	path_string = NULL;
	envp_paths = NULL;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path_string = envp[i] + 5;
		i++;
	}
	if (path_string)
	{
		envp_paths = ft_split(path_string, ':');
		if (!envp_paths)
			ft_free_close_err_exit(NULL, NULL, NULL, "Malloc error envp paths");
	}
	envp_paths = ft_add_slash_to_envp_paths(envp_paths);
	if (!envp_paths)
		exit(1);
	return (envp_paths);
}

//checks if the cmd is to be found in one of the paths specified by envp
static char	*ft_get_cmd_path(char **envp_paths, char *cmd)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (envp_paths && envp_paths[i] && cmd)
	{
		cmd_path = ft_strjoin(envp_paths[i], cmd);
		if (!cmd_path)
		{
			perror("Malloc error cmd path");
			return (NULL);
		}
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		else
			free(cmd_path);
		i++;
	}
	return (NULL);
}

char	*ft_prepare_command(char *cmd_line, char ***splitted_cmd,
								char **envp_paths)
{
	char	*cmd_path;

	cmd_path = NULL;
	*splitted_cmd = ft_get_cmd_line_elements(cmd_line);
	if (*splitted_cmd)
		cmd_path = ft_get_cmd_path(envp_paths, splitted_cmd[0][0]);
	return (cmd_path);
}
