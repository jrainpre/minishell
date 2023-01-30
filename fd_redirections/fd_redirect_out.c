/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirect_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:24:45 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/30 14:44:52 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_name(t_parse *temp, int *i)
{
	if ((ft_strlen(temp->full_cmd[*i]) > 1) && temp->full_cmd[*i][0] == '>'
		&& temp->full_cmd[*i][1] == '>' && !temp->full_cmd[*i][2])
	{
		if (temp->full_cmd[*i + 1] == NULL)
			return (0);
		else if (temp->full_cmd[*i + 1][0] == '|')
			return (0);
	}
	else if (temp->full_cmd[*i][0] == '>' && !temp->full_cmd[*i][1])
	{
		if (temp->full_cmd[*i + 1] == NULL)
			return (0);
		else if (temp->full_cmd[*i + 1][0] == '|')
			return (0);
	}
	else if (temp->full_cmd[*i][0] == '<' && !temp->full_cmd[*i][1])
	{
		if (temp->full_cmd[*i + 1] == NULL)
			return (0);
		else if (temp->full_cmd[*i + 1][0] == '|')
			return (0);
	}
	return (1);
}

int	check_valid_filename(t_parse *node)
{
	int	i;

	i = 0;
	while (node)
	{
		while (node->full_cmd[i])
		{
			if (!check_name(node, &i))
				return (0);
			i++;
		}
		i = 0;
		node = node->next;
	}
	return (1);
}

int	create_append_out(t_parse *temp, int *i)
{
	char	*old;

	old = NULL;
	if (temp->full_cmd[*i][2] != '\0')
		append_out_case1(old, temp, i);
	else
		append_out_case2(old, temp, i);
	return (1);
}

int	create_trunc_out(t_parse *temp, int *i)
{
	char	*old;

	old = NULL;
	if (temp->full_cmd[*i][1] != '\0')
		trunc_out_case1(old, temp, i);
	else
		trunc_out_case2(old, temp, i);
	return (1);
}

int	get_all_fd_out(t_prompt *struc)
{
	int		i;
	t_parse	*temp;

	i = 0;
	temp = struc->cmds;
	if (!check_valid_filename(temp))
	{
		put_error(PARSE_ERROR);
		return (0);
	}
	while (temp)
	{
		while (temp->full_cmd[i])
		{
			if (temp->full_cmd[i][0] == '>' && temp->full_cmd[i][1] == '>')
				create_append_out(temp, &i);
			else if (temp->full_cmd[i][0] == '>')
				create_trunc_out(temp, &i);
			i++;
		}
		trim_white(temp);
		temp = temp->next;
		i = 0;
	}
	return (1);
}
