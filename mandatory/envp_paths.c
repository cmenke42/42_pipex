/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:14:18 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/11 15:44:09 by cmenke           ###   ########.fr       */
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
	while(envp_paths && envp_paths[i])
	{
		result[i] = ft_strjoin(envp_paths[i], "/");
		if (!result[i])
		{
			perror("Malloc error join slash");
			ft_free_double_pointer(result);
			return (NULL);
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
			ft_error_exit("Malloc error envp cmd paths", 1);
	}
	if (envp_paths)
	{
		envp_paths = ft_add_slash_to_envp_paths(envp_paths);
		if (!envp_paths)
		{
			envp_paths = ft_free_double_pointer(envp_paths);
			exit(1);
		}
	}
	return (envp_paths);
}

char	*ft_get_cmd_path(char **envp_paths, char *cmd)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (envp_paths[i] && cmd)
	{
		cmd_path = ft_strjoin(envp_paths[i], cmd);
		if (!cmd_path)
		{
			i = 0;
			envp_paths = ft_free_double_pointer(envp_paths);
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