/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:55:41 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/11 10:09:55 by mkoller          ###   ########.fr       */
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

int do_echo(t_parse *node)
{
    int i;
    int len;
    int flag;
    
    flag = 1;
    i = 1;
    len = line_count(node->full_cmd);
    if (len >= 2)
    {
        if (!ft_strncmp(node->full_cmd[i], "-n", 2))
        {
            flag = 0;
            i++;
        }
        while (node->full_cmd[i])
        {
            ft_putstr_fd(node->full_cmd[i], 1);
            if (node->full_cmd[i+1] != NULL)
                ft_putstr_fd(" ", 1);
            i++;
        }
    }
    if (flag)
        ft_putstr_fd("\n", 1);
    return (0);   
}