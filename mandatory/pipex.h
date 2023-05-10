/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:08:38 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/10 18:37:23 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

// get_cmd_args.c
char	**ft_get_cmd_and_cmd_args(char *s);
// envp_paths.c
char	**ft_get_envp_cmd_paths(char **envp);
//childs.c
void	ft_first_child(int pipe_fds[2], char **argv, char **envp, char **envp_cmd_paths);
void	ft_last_child(int pipe_fds[2], char **argv, char **envp, char **envp_cmd_paths);
// checks.c
bool	ft_check_quote_amt(char *cmd_string);
// main.c
char	*ft_get_cmd_path(char **envp_cmd_paths, char *cmd);
bool	ft_error_ret_false(char *error_text);
void	ft_error_exit(char *error_text, int exit_code);
// remove_quotes.c
char **ft_remove_quotes(char **cmd_args);

#endif

