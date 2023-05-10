/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:08:33 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/10 16:59:30 by cmenke           ###   ########.fr       */
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

void	ft_skip_quote_block(char*s, int *i)
{
	//skip first '
	*i += 1;
	while (s[*i] && s[*i] != '\'')
		*i += 1;
}

void ft_skip_to_next_delim(char *s, char c, int *i)
{
	while(s[*i] && s[*i] != c)
	{
		if (s[*i] == '\'')
			ft_skip_quote_block(s, i);
		*i += 1;
	}
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
		if(s[i] != c)
		{
			block_count++;
			ft_skip_to_next_delim(s, c, &i);
		}
		if(!s[i])
			break ;
	}
	return (block_count);
}

char	**ft_get_cmd_blocks(char *s, char c, char **result)
{
	int		i;
	int		j;
	int		start;
	
	i = -1;
	j = -1;
	while (s[++i])
	{
		if(s[i] != c)
		{
			start = i;
			ft_skip_to_next_delim(s, c, &i);
			result[++j] = ft_substr(s, start, i - start);
		}
		if(!result[j])
		{
			perror("get cmd substrings - malloc");
			while (j >= 0)
				free(result[j--]);
			free(result);
			return (NULL);
		}
		if(!s[i])
			break ;
	}
	return (result);
}

char	**ft_get_cmd_and_cmd_args(char *s)
{
	char	**result;
	result = (char **)malloc((ft_count_cmd_blocks(s, ' ') + 1) * sizeof(char *));
	if (!result)
		perror("get cmd args - malloc");
	result = ft_get_cmd_blocks(s, ' ', result);
	return (result);
}

int	main(int argc, char **argv, char **envp)
{
	if(ft_check_quote_amt(argv[1]) == false)
		return (1);
	char **result;

	result = ft_get_cmd_and_cmd_args(argv[1]);
	int i = 0;
	while (result && result[i])
		ft_printf("args:%s\n", result[i++]);
	ft_printf("\nblock count:%d\n", ft_count_cmd_blocks(argv[1], ' '));
	ft_printf("still alive\n");
}