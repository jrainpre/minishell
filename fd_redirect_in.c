/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirect_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:40:39 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/17 15:03:09 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alloc_fd_in(t_parse *node, int cnt)
{
	if (cnt > 0)
		node->in = calloc(cnt, sizeof(int));
}

int	get_all_fd_in(t_prompt *struc)
{
	int i;
	int j;
	t_parse *temp;

	i = 0;
	j = 0;
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
				// if (temp->full_cmd[i][2] != '\0')
				// {
				//     temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i], ">>");
				//     temp->out[j] = open(temp->full_cmd[i],
				//		O_CREAT | O_WRONLY | O_APPEND, 0666);
				//     temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i],
				//		temp->full_cmd[i]);
				//     j++;
				// }
				// else
				// {
				//     temp->out[j] = open(temp->full_cmd[i+1],
				//		O_CREAT | O_WRONLY | O_APPEND, 0666);
				//     temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i],
				//		temp->full_cmd[i]);
				//     temp->full_cmd[i+1] = ft_strtrim(temp->full_cmd[i+1],
				//		temp->full_cmd[i+1]);
				//     j++;
				// }
				printf("<< redirect is not working right now!!!\n");
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
