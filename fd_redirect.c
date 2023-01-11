/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:24:45 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/11 11:46:51 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int get_all_fd(t_prompt *struc)
{
    int i;
    t_parse *temp;

    i = 0;
    temp = struc->cmds;
    while (temp)
    {
        while (temp->full_cmd[i])
        {
            if (temp->full_cmd[i][0] == '>' && temp->full_cmd[i][1] == '>')
            {
                if (temp->full_cmd[i][2] != '\0')
                {
                    temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i], ">>");
                    temp->out = open(temp->full_cmd[i], O_CREAT | O_WRONLY | O_APPEND, 0666);
                    temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i], temp->full_cmd[i]);
                }
                else 
                {
                    temp->out = open(temp->full_cmd[i+1], O_CREAT | O_WRONLY | O_APPEND, 0666);
                    temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i], temp->full_cmd[i]);
                    temp->full_cmd[i+1] = ft_strtrim(temp->full_cmd[i+1], temp->full_cmd[i+1]);
                }
            }
            else if (temp->full_cmd[i][0] == '>')
            {
                if (temp->full_cmd[i][1] != '\0')
                {
                    temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i], ">");
                    temp->out = open(temp->full_cmd[i], O_CREAT | O_WRONLY | O_TRUNC, 0666);
                    temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i], temp->full_cmd[i]);
                }
                else
                {
                    temp->out = open(temp->full_cmd[i+1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
                    temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i], temp->full_cmd[i]);
                    temp->full_cmd[i+1] = ft_strtrim(temp->full_cmd[i+1], temp->full_cmd[i+1]);   
                }
            }
            i++;
        }
        temp = temp->next;
    }
    return (0);
}