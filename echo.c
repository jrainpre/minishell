/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:55:41 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/16 15:19:49 by mkoller          ###   ########.fr       */
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

int only_n(char  *str)
{
    int i;

    i = 0;
    if (str[i] == '-')
    {
        i++;
        while (str[i])
        {
            if (str[i] != 'n')
                return (0);
            i++;
        }
    }
    else
        return (0);
    return (1);
}

void put_to_stdout(t_parse *node, int *i, int *j)
{
    int flag;
    int k;
    
    k = 0;
    flag = 1;
    if (!ft_strncmp(node->full_cmd[*i], "-n", 2) && only_n(node->full_cmd[*i]))
    {
        flag = 0;
        *i += 1;
        k = *i;
        while (node->full_cmd[k])
        {
            if (!ft_strncmp(node->full_cmd[k], "-n", 2) && only_n(node->full_cmd[k]))
            {
                node->full_cmd[k] = ft_strtrim(node->full_cmd[k], node->full_cmd[k]);
                trim_white(node);
                *i += 1;
            }
            k++;
        }
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