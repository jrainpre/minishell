/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:55:41 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/13 12:19:02 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	line_count(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void check_dup(t_parse *node, int i)
{
    dup2(node->out[i], STDOUT_FILENO);
    close(node->out[i]);
}

void restore_stdout(int saved)
{
    dup2(saved, STDOUT_FILENO);
    close(saved);
}

void put_to_stdout(t_parse *node, int *i, int *j)
{
    int flag;
    
    flag = 1;
    if (!ft_strncmp(node->full_cmd[*i], "-n", 2))
    {
        flag = 0;
        *i += 1;
    }
    while (node->full_cmd[*i])
    {
        ft_putstr_fd(node->full_cmd[*i], 1);
        if (node->full_cmd[*i+1] != NULL)
            ft_putstr_fd(" ", 1);
        *i += 1;
    }
    *i = 1;
    *j += 1;
    if (flag)
        ft_putstr_fd("\n", 1);
}

int do_echo(t_parse *node)
{
    int i;
    int j;
    int len;
    int saved;
    
    j = 0;
    i = 1;
    saved = 1;
    len = line_count(node->full_cmd);
    if (len >= 2)
    {
        while (node->out[j])
        {
            if (node->out[j] >= 3)
            {
                saved = dup(STDOUT_FILENO);
                check_dup(node, j);
                put_to_stdout(node, &i, &j);
                restore_stdout(saved);
            }
            else
                put_to_stdout(node, &i, &j);
        }
    }
    return (0);
}