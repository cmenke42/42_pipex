/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:27:40 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/11 15:31:53 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_skip_quote_block(char*s, int *i, char quote, int *cnt)
{
	//skip first '
	*i += 1;
	while (s[*i] && s[*i] != quote)
	{	*cnt += 1;
		*i += 1;
	}
	if(s[*i] == quote)
		*i += 1;
}

static int ft_count_chars(char *s)
{
	int i;
	int counter;

	counter = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			ft_skip_quote_block(s, &i, '\'', &counter);
		else if (s[i] == '"')
			ft_skip_quote_block(s, &i, '"', &counter);
		if (!s[i])
			break ;
		counter++;
		i++;
	}
	return (counter);
}

static char *ft_copy_without_quotes(char *s, int i, int j, int counter)
{
	char	*result;
	char	quote;

	counter = ft_count_chars(s);
	result = malloc((counter + 1) * sizeof(char));
	if(!result)
		return (NULL);
	while (s[i])
	{
		if(s[i] == '\'' || s[i] == '"')
		{
			if (s[i] == '\'')
				quote = s[i++];
			else if (s[i] == '"')
				quote = s[i++];
			while (s[i] && s[i] != quote)
				result[j++] = s[i++];
			if (!s[i++])
				break ;
		}
		result[j++] = s[i++];
	}
	result[j] = '\0';
	return (result);
}

char **ft_remove_quotes(char **cmd_args)
{
	int		i;
	char	*temp;
	
	i = 0;
	while (cmd_args[i])
	{
		temp = ft_copy_without_quotes(cmd_args[i], 0, 0, 0);
		if(!temp)
		{
			perror("remove quotes - malloc");
			ft_free_double_pointer(cmd_args);
			return (NULL);
		}
		free(cmd_args[i]);
		cmd_args[i] = temp;
		i++;
	}
	return (cmd_args);
}