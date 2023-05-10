/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:08:06 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/10 11:59:50 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	ft_check_quote_amt(char *cmd_string)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (cmd_string[i])
	{
		if (cmd_string[i] == '\'')
			single_quotes++;
		else if (cmd_string[i] == '"')
			double_quotes++;
		i++;
	}
	if (single_quotes % 2 == 0 && double_quotes % 2 == 0)
		return (true);
	return (false);
}