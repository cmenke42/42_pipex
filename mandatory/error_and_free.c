/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:08:33 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/19 16:30:06 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_free_double_pointer(char **ptr)
{
	int	i;

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
		if (files_fd[0] != -1)
			close(files_fd[0]);
		if (files_fd[1] != -1)
			close(files_fd[1]);
	}
	if (pipe_fd)
	{
		if (pipe_fd[0] != -1)
			close(pipe_fd[0]);
		if (pipe_fd[1] != -1)
			close(pipe_fd[1]);
	}
}

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

int	ft_error_ret_1(char *error_text)
{
	perror(error_text);
	return (1);
}

void	ft_close_standard_fd(int fd_0, int fd_1, int fd_2)
{
	close(fd_0);
	close(fd_1);
	close(fd_2);
}
