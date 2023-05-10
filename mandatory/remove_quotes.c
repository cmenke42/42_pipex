/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:27:40 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/10 23:07:36 by cmenke           ###   ########.fr       */
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
		temp = ft_copy_without_quotes(cmd_args[i]);
		if(!temp)
		{
			perror("copy without quotes - malloc");
			ft_free_double_pointer(cmd_args);
			return (NULL);
		}
		free(cmd_args[i]);
		cmd_args[i] = temp;
		i++;
	}
	return (cmd_args);
}