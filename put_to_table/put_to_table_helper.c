/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_to_table_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:36:05 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 14:06:31 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_pipes(char **split)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (split[i])
	{
		if (split[i][0] == '|')
			count++;
		i++;
	}
	return (count);
}

int	count_redirect(char **split)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (split[i])
	{
		if (split[i][0] == '>' || split[i][0] == '<')
			count++;
		i++;
	}
	return (count);
}

int	pointer_count(char **str, int *i)
{
	int	count;

	count = 0;
	while (str[*i] && str[*i][0] != '|')
	{
		count++;
		*i += 1;
	}
	*i += 1;
	return (count);
}

void	put_table_non_pipe(char **str, t_parse *temp, int *i, int *j)
{
	temp->full_cmd[*j] = ft_strdup(str[*i]);
	*j += 1;
	*i += 1;
}

void	put_table_pipe(char **str, t_parse *temp, int *k, int *i)
{
	if (temp != NULL)
		temp->full_cmd = ft_calloc((pointer_count(str, k) + 1), sizeof(char *));
	*i += 1;
}
