/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirect_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:24:45 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/27 09:36:13 by jrainpre         ###   ########.fr       */
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

int	trim_white(t_parse *node)
{
	int	i;
	char	*old;
	
	i = 0;
	if (**node->full_cmd == '\0')
	{
		while (node->full_cmd[i])
		{
			if (node->full_cmd[i + 1])
			{
				old = node->full_cmd[i];
				node->full_cmd[i] = ft_strdup(node->full_cmd[i + 1]);
			}
			else
			{
				old = node->full_cmd[i];
				node->full_cmd[i] = ft_strdup("");
			}
			i++;
		}
	}
	return (0);
}

int	create_append_out(t_parse *temp, int *i)
{
	char 	*old;
	
	if (temp->full_cmd[*i][2] != '\0')
	{
		old =temp->full_cmd[*i];
		temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i], ">>");
		free(old);
		temp->out = open(temp->full_cmd[*i],
								O_CREAT | O_WRONLY | O_APPEND,
								0666);
		old =temp->full_cmd[*i];						
		temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i],
										temp->full_cmd[*i]);
		free(old);
	}
	else
	{
		temp->out = open(temp->full_cmd[*i + 1],
								O_CREAT | O_WRONLY | O_APPEND,
								0666);
		old =temp->full_cmd[*i];						
		temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i],
										temp->full_cmd[*i]);
		free(old);
		old =temp->full_cmd[*i + 1];
		temp->full_cmd[*i + 1] = ft_strtrim(temp->full_cmd[*i + 1],
											temp->full_cmd[*i + 1]);
		free(old);
	}
	return (1);
}

int	create_trunc_out(t_parse *temp, int *i)
{
	char 	*old;
	
	if (temp->full_cmd[*i][1] != '\0')
	{
		old=temp->full_cmd[*i];
		temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i], ">");
		temp->out = open(temp->full_cmd[*i],
								O_CREAT | O_WRONLY | O_TRUNC,
								0666);
		free(old);
		old =temp->full_cmd[*i];
		temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i],
										temp->full_cmd[*i]);
		free(old);
	}
	else
	{
		temp->out = open(temp->full_cmd[*i + 1],
								O_CREAT | O_WRONLY | O_TRUNC,
								0666);
		old =temp->full_cmd[*i];
		temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i],
										temp->full_cmd[*i]);
		free(old);
		old =temp->full_cmd[*i + 1];
		temp->full_cmd[*i + 1] = ft_strtrim(temp->full_cmd[*i + 1],
											temp->full_cmd[*i + 1]);
		free(old);
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
		i = 0;
	}
	return (1);
}
