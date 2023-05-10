/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:08:33 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/10 22:21:16 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	ft_close_fd(int *files_fd, int *pipe_fd)
{
	if (files_fd)
	{
		close(files_fd[0]);
		close(files_fd[1]);
	}
	if (pipe_fd)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

//exits only on error
void	ft_free_close_err_exit(int *files_fd, int *pipe_fd, char **envp_paths,
							 char *error_text)
{
	ft_close_fd(files_fd, pipe_fd);
	envp_paths = ft_free_double_pointer(envp_paths);
	if (error_text)
	{
		perror(error_text);
		exit(1);
	}
}

bool	ft_error_ret_false(char *error_text)
{
	perror(error_text);
	return (false);
}

void	ft_error_exit(char *error_text, int exit_code)
{
	if (exit_code != 0)
		perror(error_text);
	exit(exit_code);
}
