/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:27:40 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/10 22:38:21 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char *ft_copy_without_quotes(char *s)
{
	int	i;
	int	j;
	int	counter;
	char *result;

	counter = 0;
	i = -1;
	while (s[++i])
		if(s[i] != '\'')
			counter++;
	result = malloc((counter + 1) * sizeof(char));
	if(!result)
	{
		perror("remove quotes - malloc");
		return (NULL);
	}
	i = -1;
	j = 0;
	while (s[++i])
		if(s[i] != '\'')
			result[j++] = s[i];
	result[j] = 0;
	return (result);
}

static void	ft_free_all_args(char **cmd_args)
{
	int i;

	i = 0;
	perror("copy without quotes - malloc");
	if (cmd_args)
	{
		while (cmd_args[i])
			free(cmd_args[i++]);
		free(cmd_args);
	}
}

char **ft_remove_quotes(char **cmd_args)
{
	int		i;
	char	*temp;
	
	i = 0;
	while (cmd_args && cmd_args[i])
	{
		temp = ft_copy_without_quotes(cmd_args[i]);
		if(!temp)
		{
			ft_free_all_args(cmd_args);
			return (NULL);
		}
		free(cmd_args[i]);
		cmd_args[i] = temp;
		i++;
	}
	return (cmd_args);
}