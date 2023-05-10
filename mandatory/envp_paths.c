/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:14:18 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/10 19:00:20 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_add_slash_to_envp_paths(char **envp)
{
	char	**result;
	int		i;

	i = 0;
	while (envp && envp[i])
		i++;
	result = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!result)
		ft_error_exit("Malloc error add slash", 1);
	i = 0;
	while(envp && envp[i])
	{
		result[i] = ft_strjoin(envp[i], "/");
		if (!result[i])
		{
			while (i >= 0)
				free(result[i--]);
			free(result);
			ft_error_exit("Malloc error add slash", 1);
		}
		i++;
	}
	return (result);
}

char	**ft_get_envp_cmd_paths(char **envp)
{
	int		i;
	char	*path_string;
	char	**envp_cmd_paths;

	i = 0;
	path_string = NULL;
	envp_cmd_paths = NULL;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path_string = envp[i] + 5;
		i++;
	}
	if (path_string)
	{
		envp_cmd_paths = ft_split(path_string, ':');
		if (!envp_cmd_paths)
			ft_error_exit("Malloc error envp cmd paths", 1);
	}
	if (envp_cmd_paths)
		envp_cmd_paths = ft_add_slash_to_envp_paths(envp_cmd_paths);
	return (envp_cmd_paths);
}
