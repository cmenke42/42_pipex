/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd_line_elements.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:37:42 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/12 15:21:38 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	**ft_get_cmd_line_sub(char *cmd_line, int *i_j, bool *split,
								char **splitted_cmd_line)
{
	int		start;

	start = i_j[0];
	if (cmd_line[i_j[0]] == '\'' || cmd_line[i_j[0]] == '\"')
	{
		if (ft_skip_quote_block(cmd_line, &i_j[0], split))
			splitted_cmd_line[++(i_j[1])] = ft_substr(cmd_line,
					start, i_j[0] - start);
	}
	else if (ft_skip_to_next_delimiter(cmd_line, &i_j[0], split, ' '))
	{
		splitted_cmd_line[++(i_j[1])] = ft_substr(cmd_line,
				start, i_j[0] - start);
	}
	if (i_j[1] >= 0 && !splitted_cmd_line[i_j[1]])
	{
		perror("cmd_line_sub - malloc");
		return (ft_free_double_pointer(splitted_cmd_line));
	}
	return (splitted_cmd_line);
}

static char	**ft_split_cmd_line(char *cmd_line, char c,
								char **splitted_cmd_line)
{
	int		i_j[2];
	bool	split;

	i_j[0] = 0;
	i_j[1] = -1;
	split = true;
	while (cmd_line && cmd_line[i_j[0]])
	{
		if (cmd_line[i_j[0]] != c)
		{
			splitted_cmd_line = ft_get_cmd_line_sub(cmd_line, i_j, &split,
					splitted_cmd_line);
			if (!splitted_cmd_line)
				return (NULL);
		}		
		if (cmd_line[i_j[0]] && cmd_line[i_j[0]] == c)
		{
			split = true;
			i_j[0]++;
		}
	}
	return (splitted_cmd_line);
}

char	**ft_get_cmd_line_elements(char *cmd_line)
{
	char	**splitted_cmd_line;
	int		count;

	if (ft_check_equal_quote_amt(cmd_line) == false)
		return (NULL);
	count = ft_count_cmd_line_elements(cmd_line, ' ');
	if (count == 0)
		return (NULL);
	splitted_cmd_line = (char **)ft_calloc((count + 1), sizeof(char *));
	if (!splitted_cmd_line)
	{
		perror("splitted_cmd_line - malloc");
		return (NULL);
	}
	splitted_cmd_line = ft_split_cmd_line(cmd_line, ' ', splitted_cmd_line);
	if(splitted_cmd_line)
		splitted_cmd_line = ft_remove_quotes_from_elements(splitted_cmd_line);
	return (splitted_cmd_line);
}
