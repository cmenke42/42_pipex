/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:08:38 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/24 02:08:55 by cmenke           ###   ########.fr       */
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
	int		files_fd[2];
	int		pipe_fds[2];
}				t_vars;

//process_cmd_line - Folder
// count_elements.c
bool	ft_check_equal_quote_amt(char *s);
int		ft_skip_quote_block(char *cmd_line, int *i, bool *split);
int		ft_skip_to_next_delimiter(char *cmd_line, int *i, bool *split, char c);
int		ft_count_cmd_line_elements(char *cmd_line, char c);
// ft_get_cmd_line_elements.c
char	**ft_get_cmd_line_elements(char *cmd_line);
// remove_quotes.c
char	**ft_remove_quotes_from_elements(char **splitted_cmd_line);
//childs.c
void	ft_first_child(char **argv, char **envp_paths,
			t_vars *vars, char **envp);
void	ft_last_child(char **argv, char **envp_paths,
			t_vars *vars, char **envp);
// envp_and_cmd_paths.c
char	**ft_get_envp_paths(char **envp);
char	*ft_prepare_command(char *cmd_line,
			char ***splitted_cmd, char **envp_paths);
// error_and_free.c
char	**ft_free_double_pointer(char **ptr);
void	ft_close_fd(int *files_fd, int *pipe_fd);
void	ft_free_close_err_exit(int *files_fd, int *pipe_fd, char **envp_paths,
			char *error_text);
int		ft_error_ret_exit_code(char *error_text, int exit_code);
void	ft_close_standard_fd(void);

#endif
