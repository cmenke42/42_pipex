/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:08:33 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/09 22:35:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	ft_check_quote_amt(char *cmd_string)
{
	int	i;
	int	single_quotes;

	i = 0;
	single_quotes = 0;
	while (cmd_string[i])
	{
		if (cmd_string[i] == '\'')
			single_quotes++;
		i++;
	}
	if (single_quotes % 2 == 0)
		return (true);
	return (false);
}

// start with i = -1
int	ft_count_cmd_blocks(char *cmd_string, char c)
{
	int	block_count;
	int	i;
	
	block_count = 0;
	i = -1;
	while (cmd_string[++i])
	{
		if (cmd_string[i] != c)
		{
			if (cmd_string[i] == c || block_count == 0)
				block_count++;
			if (cmd_string[i] == '\'')
				while (cmd_string[++i] && cmd_string[i] != '\'')
					;
			else
				while (cmd_string[i] && cmd_string[i] != c && cmd_string[i] != '\'')
					i++;
		}
		if (!cmd_string[i])
			break ;
	}
	return (block_count);
}

// //start with i = -1
// int	ft_count_cmd_blocks(char *cmd_string, char c, bool allocate, int i)
// {
// 	int	block_count;
	
// 	block_count = 0;
// 	while (cmd_string[++i])
// 	{
// 		if (cmd_string[i] != c && cmd_string[i] != '\'')
// 		{
// 			if (allocate == true)
// 				ft_allocate_substring(cmd_string, )
// 			block_count++;
// 			while (cmd_string[i] && cmd_string[i] != c && cmd_string[i] != '\'')
// 				i++;
// 		}
// 		if (cmd_string[i] == '\'')
// 		{
// 			while (cmd_string[++i] && cmd_string[i] != '\'')
// 				;
// 			if (cmd_string[i])
// 				i++;
// 		}
// 		if (!cmd_string[i])
// 			break ;
// 	}
// 	return (block_count);
// }


int	main(int argc, char **argv, char **envp)
{
	if(ft_check_quote_amt(argv[1]) == false)
		return (1);
	ft_printf("block count:%d\n", ft_count_cmd_blocks(argv[1], ' '));
	ft_printf("still alive\n");
}