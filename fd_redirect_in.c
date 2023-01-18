/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirect_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:40:39 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/18 11:46:53 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alloc_fd_in(t_parse *node, int cnt)
{
	if (cnt > 0)
		node->in = calloc(cnt, sizeof(int));
}

int	ft_strncmp_special(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
	if (i < n)
	{
		return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
	}
	return (0);
}

char *heredoc(char *limit)
{
	char *str[2];
	char *temp;
	int len;

	len = 0;
	str[0] = NULL;
	str[1] = NULL;
	while (!str[0] || (ft_strncmp_special(str[0], limit, len)) || (ft_strlen(limit) != len))
	{
		temp = str[1];
		str[1] = ft_strjoin(str[1], str[0]);
		free(temp);
		free(str[0]);
		str[0] = readline("heredoc> ");
		if (!str[0])
		{
			printf("ERROR!!");
			break ;
		}
		temp = str[0];
		str[0] = ft_strjoin(str[0], "\n");
		free(temp);
		len = ft_strlen(str[0]) - 1;
	}
	free(str[0]);
	return (str[1]);
}

int	get_all_fd_in(t_prompt *struc)
{
	int i;
	int j;
	t_parse *temp;
	char *str;

	i = 0;
	j = 0;
	str = NULL;
	temp = struc->cmds;
	if (!check_valid_filename(temp))
	{
		ft_putstr_fd(PARSE_ERROR, 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}
	while (temp)
	{
		alloc_fd_in(temp, count_redirect(temp->full_cmd));
		while (temp->full_cmd[i])
		{
			if (temp->full_cmd[i][0] == '<' && temp->full_cmd[i][1] == '<')
			{
				if (temp->full_cmd[i][2] != '\0')
				{
				    temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i], "<<");
				    str = heredoc(temp->full_cmd[i]);
				    temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i],
						temp->full_cmd[i]);
					ft_putstr_fd(str, 1);
					free(str);
				    j++;
				}
				else
				{
				    temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i], "<<");
					str = heredoc(temp->full_cmd[i+1]);
				    temp->full_cmd[i+1] = ft_strtrim(temp->full_cmd[i+1],
						temp->full_cmd[i+1]);
					ft_putstr_fd(str, 1);
					free(str);
				    j++;
				}
			}
			else if (temp->full_cmd[i][0] == '<')
			{
				if (temp->full_cmd[i][1] != '\0')
				{
					temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i], "<");
					temp->in[j] = open(temp->full_cmd[i], O_RDONLY, 0666);
					if (temp->in[j] == -1)
					{
						ft_putstr_fd("minishell: no such file or directory: ",
								1);
						ft_putstr_fd(temp->full_cmd[i], 1);
						ft_putstr_fd("\n", 1);
					}
					temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i],
							temp->full_cmd[i]);
					j++;
				}
				else
				{
					temp->in[j] = open(temp->full_cmd[i + 1], O_RDONLY, 0666);
					if (temp->in[j] == -1)
					{
						ft_putstr_fd("minishell: no such file or directory: ",
								1);
						ft_putstr_fd(temp->full_cmd[i + 1], 1);
						ft_putstr_fd("\n", 1);
					}
					temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i],
							temp->full_cmd[i]);
					temp->full_cmd[i + 1] = ft_strtrim(temp->full_cmd[i + 1],
							temp->full_cmd[i + 1]);
					j++;
				}
			}
			i++;
		}
		trim_white(temp);
		temp = temp->next;
	}
	return (1);
}
