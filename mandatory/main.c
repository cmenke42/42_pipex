/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:08:33 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/10 11:48:07 by user             ###   ########.fr       */
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

// // start with i = -1
// int	ft_count_cmd_blocks(char *cmd_string, char c)
// {
// 	int	block_count;
// 	int	i;
	
// 	block_count = 0;
// 	i = -1;
// 	while (cmd_string[++i])
// 	{
// 		if (cmd_string[i] != c)
// 		{
// 			if (cmd_string[i] == c || block_count == 0)
// 				block_count++;
// 			if (cmd_string[i] == '\'')
// 				while (cmd_string[++i] && cmd_string[i] != '\'')
// 					;
// 			else
// 				while (cmd_string[i] && cmd_string[i] != c && cmd_string[i] != '\'')
// 					i++;
// 		}
// 		if (!cmd_string[i])
// 			break ;
// 	}
// 	return (block_count);
// }

int	ft_skip_quote_block(char*s, int i)
{
	//skip first '
	i++;
	while (s[i] && s[i] != '\'')
		i++;
	return (i);
}

bool	ft_search_for_valid_char(char*s, char c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if(s[i] != c && s[i] != '\'')
			return (true);
		i++;
	}
	return (false);
}

//start with i = -1
int	ft_count_cmd_blocks(char *s, char c)
{
	int	block_count;
	int	i;
	
	block_count = 0;
	i = -1;
	while (s[++i])
	{
		ft_printf("char:%c\n", s[i]);
		if (s[i] != c)
		{
			if (s[i] != '\'' || (i > 0 && 
				(s[i - 1] == ' ' && s[i] == '\'' && s[i + 1] != '\''))
				|| i == 0 && (s[i] == '\'' && s[i + 1] != '\''))
			{
				block_count++;
				if (s[i] == '\'')
					i = ft_skip_quote_block(s, i);
				else
				{
					while (s[i] != c && s[i])
						i++;
				}
			}
			else
				i = ft_skip_quote_block(s, i);
			if (s[i] == '\0')
				break ;
		}
	}
	if (block_count == 0 && ft_search_for_valid_char(s, c) == true)
		block_count++;
	return (block_count);
}
// //start with i = -1
// int	ft_count_cmd_blocks(char *s, char c)
// {
// 	int	block_count;
// 	int	i;
	
// 	block_count = 0;
// 	i = 0;
// 	while(s[i])
// 	{
// 		if (s[i] != c)
// 		{
// 			if ((s[i] != c && s[i] != '\'')
// 				|| (s[i] && s[i] == '\''
// 				&& s[i + 1] != '\''))
// 					block_count++;
// 			while (s[i] && s[i] != c && s[i] != '\'')
// 				i++;
// 		}
// 		else if (s[i] == '\'')
// 		{
		
// 		}
// 		if (!s[i])
// 			break ;
// 		// if (s[i] == c)
// 		// {
// 		// 	while (s[i] && s[i] == c && s[i] != '\'')
// 		// 		i++;
// 		// 	if ((s[i] != c && s[i] != '\'')
// 		// 		|| (s[i] && s[i] == '\''
// 		// 		&& s[i + 1] != '\''))
// 		// 			block_count++;
// 		// }
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