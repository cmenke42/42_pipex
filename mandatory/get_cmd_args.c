/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:08:06 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/10 22:37:52 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_skip_quote_block(char*s, int *i)
{
	//skip first '
	*i += 1;
	while (s[*i] && s[*i] != '\'')
		*i += 1;
}

static void ft_skip_to_next_delim(char *s, char c, int *i)
{
	while(s[*i] && s[*i] != c)
	{
		if (s[*i] == '\'')
			ft_skip_quote_block(s, i);
		*i += 1;
	}
}

//start with i = -1
static int	ft_count_cmd_blocks(char *s, char c)
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

static char	**ft_get_cmd_blocks(char *s, char c, char **result)
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
	
	if(ft_check_quote_amt(s) == false)
		return (NULL);
	result = (char **)malloc((ft_count_cmd_blocks(s, ' ') + 1) * sizeof(char *));
	if (!result)
		perror("get cmd args - malloc");
	result = ft_get_cmd_blocks(s, ' ', result);
	if (result)
		result = ft_remove_quotes(result);
	return (result);
}