/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirect_out_helpter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:23:34 by jrainpre          #+#    #+#             */
/*   Updated: 2023/02/13 11:44:50 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	trim_white(t_parse *node)
{
	int		i;
	char	*old;

	i = -1;
	if (*node->full_cmd == NULL)
		return (0);
	if (**node->full_cmd == '\0')
	{
		while (node->full_cmd[++i])
		{
			if (node->full_cmd[i + 1])
			{
				old = node->full_cmd[i];
				node->full_cmd[i] = ft_strdup(node->full_cmd[i + 1]);
				free(old);
			}
			else
			{
				old = node->full_cmd[i];
				node->full_cmd[i] = ft_strdup("");
				free(old);
			}
		}
	}
	return (0);
}

void	append_out_case1(char *old, t_parse *temp, int *i)
{
	old = temp->full_cmd[*i];
	temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i], ">>");
	free(old);
	temp->out = open(temp->full_cmd[*i], \
	O_CREAT | O_WRONLY | O_APPEND, 0644);
	old = temp->full_cmd[*i];
	temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i], \
	temp->full_cmd[*i]);
	free(old);
}

void	append_out_case2(char *old, t_parse *temp, int *i)
{
	temp->out = open(temp->full_cmd[*i + 1], \
	O_CREAT | O_WRONLY | O_APPEND, 0644);
	old = temp->full_cmd[*i];
	temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i], \
	temp->full_cmd[*i]);
	free(old);
	old = temp->full_cmd[*i + 1];
	temp->full_cmd[*i + 1] = ft_strtrim(temp->full_cmd[*i + 1], \
	temp->full_cmd[*i + 1]);
	free(old);
}

void	trunc_out_case1(char *old, t_parse *temp, int *i)
{
	old = temp->full_cmd[*i];
	temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i], ">");
	temp->out = open(temp->full_cmd[*i], \
	O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(old);
	old = temp->full_cmd[*i];
	temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i], \
	temp->full_cmd[*i]);
	free(old);
}

void	trunc_out_case2(char *old, t_parse *temp, int *i)
{
	temp->out = open(temp->full_cmd[*i + 1], \
	O_CREAT | O_WRONLY | O_TRUNC, 0644);
	old = temp->full_cmd[*i];
	temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i], \
	temp->full_cmd[*i]);
	free(old);
	old = temp->full_cmd[*i + 1];
	temp->full_cmd[*i + 1] = ft_strtrim(temp->full_cmd[*i + 1], \
	temp->full_cmd[*i + 1]);
	free(old);
}
