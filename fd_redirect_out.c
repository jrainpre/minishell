/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirect_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:24:45 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/24 14:44:50 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		i;
	t_parse	*temp;

	i = 0;
	temp = node;
	while (temp)
	{
		while (temp->full_cmd[i])
		{
			check_name(temp, &i);
			i++;
		}
		i = 0;
		temp = temp->next;
	}
	temp = NULL;
	return (1);
}

void	alloc_fd_out(t_parse *node, int cnt)
{
	if (cnt > 0)
		node->out = calloc(cnt, sizeof(int));
}

int	trim_white(t_parse *node)
{
	int	i;

	i = 0;
	if (**node->full_cmd == '\0')
	{
		while (node->full_cmd[i])
		{
			node->full_cmd[i] = node->full_cmd[i + 1];
			i++;
		}
	}
	return (0);
}

int	create_append_out(t_parse *temp, int *i)
{
	if (temp->full_cmd[*i][2] != '\0')
	{
		temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i], ">>");
		temp->out = open(temp->full_cmd[*i],
								O_CREAT | O_WRONLY | O_APPEND,
								0666);
		temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i],
										temp->full_cmd[*i]);
	}
	else
	{
		temp->out = open(temp->full_cmd[*i + 1],
								O_CREAT | O_WRONLY | O_APPEND,
								0666);
		temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i],
										temp->full_cmd[*i]);
		temp->full_cmd[*i + 1] = ft_strtrim(temp->full_cmd[*i + 1],
											temp->full_cmd[*i + 1]);
	}
	return (1);
}

int	create_trunc_out(t_parse *temp, int *i)
{
	if (temp->full_cmd[*i][1] != '\0')
	{
		temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i], ">");
		temp->out = open(temp->full_cmd[*i],
								O_CREAT | O_WRONLY | O_TRUNC,
								0666);
		temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i],
										temp->full_cmd[*i]);
	}
	else
	{
		temp->out = open(temp->full_cmd[*i + 1],
								O_CREAT | O_WRONLY | O_TRUNC,
								0666);
		temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i],
										temp->full_cmd[*i]);
		temp->full_cmd[*i + 1] = ft_strtrim(temp->full_cmd[*i + 1],
											temp->full_cmd[*i + 1]);
	}
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
	}
	return (1);
}
