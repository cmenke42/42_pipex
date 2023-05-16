/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:08:38 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/16 16:44:28 by cmenke           ###   ########.fr       */
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
	int		files_fd[2];
}				t_vars;


//delete
void ft_print_double_pointer(char **str);


// envp_paths.c
char	**ft_get_envp_paths(char **envp);
char	*ft_get_cmd_path(char **envp_cmd_paths, char *cmd);
//childs.c
void	ft_first_child(int pipe_fds[2], int file_fds[2], char **envp_paths,
														t_vars *vars);
void	ft_last_child(int pipe_fds[2], int files_fd[2], char **envp_paths,
														t_vars *vars);
// checks.c
bool	ft_check_quote_amt(char *cmd_string);
// main.c
char	*ft_prepare_command(char *cmd_line, char **envp_paths,
								 char **splitted_cmd, char **envp);
void	ft_error_free_exit(char *error_text, char **envp_cmd_paths,
								int pipe_fds[2], int files_fd[2]);


char	**ft_free_double_pointer(char **ptr);
char	*ft_get_cmd_path(char **envp_cmd_paths, char *cmd);
bool	ft_error_ret_false(char *error_text);
void	ft_error_exit(char *error_text, int exit_code);
// error_and_free.c
void	ft_free_close_err_exit(int *files_fd, int *pipe_fd, char **envp_paths,
							 char *error_text);
void	ft_error_exit(char *error_text, int exit_code);
char	**ft_free_double_pointer(char **ptr);
void	ft_close_fd(int *files_fd, int *pipe_fd);

//process_cmd_line - Folder
int		ft_count_cmd_line_elements(char *cmd_line, char c);
int		ft_skip_quote_block(char *cmd_line, int *i, bool *split);
int		ft_skip_to_next_delimiter(char *cmd_line, int *i, bool *split, char c);
bool	ft_check_equal_quote_amt(char *s);
char	**ft_get_cmd_line_elements(char *cmd_line);
char	**ft_remove_quotes_from_elements(char **splitted_cmd_line);

#endif

