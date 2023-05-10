/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:08:38 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/10 11:55:23 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_vars
{
	char	**envp;
	char	**argv;
}				t_vars;

// get_cmd_args.c
char	**ft_get_cmd_and_cmd_args(char *s);
// envp_paths.c
char	**ft_get_envp_paths(char **envp);
char	*ft_get_cmd_path(char **envp_cmd_paths, char *cmd);
//childs.c
void	ft_first_child(int pipe_fds[2], int file_fd[2], t_vars vars, char **envp_paths);
void	ft_last_child(int pipe_fds[2], int file_fd[2], t_vars vars, char **envp_paths);
// checks.c
bool	ft_check_quote_amt(char *cmd_string);
// main.c
char	**ft_free_double_pointer(char **ptr);
char	*ft_get_cmd_path(char **envp_cmd_paths, char *cmd);
bool	ft_error_ret_false(char *error_text);
void	ft_error_exit(char *error_text, int exit_code);
// remove_quotes.c
char **ft_remove_quotes(char **cmd_args);
// error_and_free.c
void	ft_free_close_err_exit(int *files_fd, int *pipe_fd, char **envp_paths,
							 char *error_text);
void	ft_error_exit(char *error_text, int exit_code);
char	**ft_free_double_pointer(char **ptr);
void	ft_close_fd(int *files_fd, int *pipe_fd);

#endif

