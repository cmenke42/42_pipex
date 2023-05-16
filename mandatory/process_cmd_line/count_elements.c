/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:37:12 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/16 19:22:14 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

bool	ft_check_equal_quote_amt(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			while (s[++i] && s[i] != '\'')
				;
			if (s[i] != '\'')
				return (false);
		}
		else if (s[i] == '\"')
		{
			while (s[++i] && s[i] != '\"')
				;
			if (s[i] != '\"')
				return (false);
		}
		if (s[i])
			i++;
	}	
	return (true);
}

int	ft_skip_quote_block(char *cmd_line, int *i, bool *split)
{
	char	quote;
	int		count;
	int		start;

	count = 0;
	start = *i;
	while (cmd_line[*i] && (cmd_line[*i] == '\'' || cmd_line[*i] == '\"'))
	{
		quote = '\"';
		if (cmd_line[*i] == '\'')
			quote = '\'';
		while (cmd_line[++(*i)] && cmd_line[*i] != quote)
			;
		if (*i - start > 1 && *split == true)
		{
			count = 1;
			*split = false;
		}
		if (cmd_line[*i] && cmd_line[*i] == quote)
			start = ++(*i);
	}
	return (count);
}

int	ft_skip_to_next_delimiter(char *cmd_line, int *i, bool *split, char c)
{
	int	count;

	count = 0;
	while (cmd_line[*i] && cmd_line[*i] != c
		&& cmd_line[*i] != '\'' && cmd_line[*i] != '\"')
		*i += 1;
	if (*split == true)
	{
		*split = false;
		count = 1;
	}
	return (count);
}

int	ft_count_cmd_line_elements(char *cmd_line, char c)
{
	int		i;
	int		count;
	bool	split;

	i = 0;
	count = 0;
	split = true;
	while (cmd_line && cmd_line[i])
	{
		if (cmd_line[i] != c)
		{
			if (cmd_line[i] == '\'' || cmd_line[i] == '\"')
				count += ft_skip_quote_block(cmd_line, &i, &split);
			else
				count += ft_skip_to_next_delimiter(cmd_line, &i, &split, c);
		}
		if (cmd_line[i] && cmd_line[i] == c)
		{
			split = true;
			i++;
		}
	}
	return (count);
}
