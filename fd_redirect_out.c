/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirect_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:24:45 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/12 13:41:47 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void alloc_fd_out(t_parse *node, int cnt)
{
    if (cnt > 0)
        node->out = calloc(cnt, sizeof(int));
}

int trim_white(t_parse *node)
{
    int i;

    i = 0;
    if (**node->full_cmd == '\0')
    {   
        while (node->full_cmd[i])
        {
            node->full_cmd[i] = node->full_cmd[i+1];
            i++;
        }  
    }
    return (0);
}

int get_all_fd_out(t_prompt *struc)
{
    int i;
    int j;
    t_parse *temp;

    i = 0;
    j = 0;
    temp = struc->cmds;
    while (temp)
    {
        alloc_fd_out(temp, count_redirect(temp->full_cmd));
        while (temp->full_cmd[i])
        {
            if (temp->full_cmd[i][0] == '>' && temp->full_cmd[i][1] == '>')
            {
                if (temp->full_cmd[i][2] != '\0')
                {
                    temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i], ">>");
                    temp->out[j] = open(temp->full_cmd[i], O_CREAT | O_WRONLY | O_APPEND, 0666);
                    temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i], temp->full_cmd[i]);
                    j++;
                }
                else 
                {
                    temp->out[j] = open(temp->full_cmd[i+1], O_CREAT | O_WRONLY | O_APPEND, 0666);
                    temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i], temp->full_cmd[i]);
                    temp->full_cmd[i+1] = ft_strtrim(temp->full_cmd[i+1], temp->full_cmd[i+1]);
                    j++;
                }
            }
            else if (temp->full_cmd[i][0] == '>')
            {
                if (temp->full_cmd[i][1] != '\0')
                {
                    temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i], ">");
                    temp->out[j] = open(temp->full_cmd[i], O_CREAT | O_WRONLY | O_TRUNC, 0666);
                    temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i], temp->full_cmd[i]);
                    j++;
                }
                else
                {
                    temp->out[j] = open(temp->full_cmd[i+1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
                    temp->full_cmd[i] = ft_strtrim(temp->full_cmd[i], temp->full_cmd[i]);
                    temp->full_cmd[i+1] = ft_strtrim(temp->full_cmd[i+1], temp->full_cmd[i+1]);
                    j++;
                }
            }
            i++;
        }
        trim_white(temp);
        temp = temp->next;
    }
    return (0);
}