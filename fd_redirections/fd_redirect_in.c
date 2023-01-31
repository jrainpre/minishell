/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirect_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:40:39 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/31 10:26:43 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

char	*heredoc(char *limit)
{
	char	*str[2];
	char	*temp;
	int		len;

	len = 0;
	str[0] = NULL;
	str[1] = NULL;
	while (!str[0] || (ft_strncmp_special(str[0], limit, len))
		|| (ft_strlen(limit) != len))
	{
		heredoc_helper(temp, str);
		if (!str[0])
		{
			print_warning(limit);
			return (NULL);
		}
		temp = str[0];
		str[0] = ft_strjoin(str[0], "\n");
		free(temp);
		len = ft_strlen(str[0]) - 1;
	}
	free(str[0]);
	return (str[1]);
}

int	create_trunc_in(t_parse *temp, int *i)
{
	if (temp->full_cmd[*i][1] != '\0')
	{
		temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i], "<");
		temp->in = open(temp->full_cmd[*i], O_RDONLY, 0644);
		if (temp->in == -1)
			print_file_error(temp->full_cmd, *i);
		temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i], \
		temp->full_cmd[*i]);
	}
	else
	{
		temp->in = open(temp->full_cmd[*i + 1], O_RDONLY, 0644);
		if (temp->in == -1)
			print_file_error(temp->full_cmd, *i + 1);
		temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i], \
		temp->full_cmd[*i]);
		temp->full_cmd[*i + 1] = ft_strtrim(temp->full_cmd[*i + 1], \
		temp->full_cmd[*i + 1]);
	}
	return (1);
}

int	heredoc_file(t_parse *node, t_prompt *struc)
{
	int		fd;
	char	*str;
	char	*temp;

	temp = ft_itoa(struc->rand);
	str = ft_strjoin(".", temp);
	free(temp);
	fd = open(str, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
	{
		put_error("ERROR!!");
		return (0);
	}
	write(fd, node->heredoc, ft_strlen(node->heredoc));
	close(fd);
	fd = open(str, O_RDONLY, 0777);
	node->in = fd;
	struc->rand--;
	free(str);
	return (0);
}

int	get_all_fd_in(t_prompt *struc)
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
			if (fd_in_helper(temp, &i, struc) == 0)
				return (0);
		}
		trim_white(temp);
		temp = temp->next;
		i = 0;
	}
	return (1);
}
