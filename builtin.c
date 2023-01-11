/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:42:38 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/11 14:58:39 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin(t_parse *node, t_prompt *struc)
{
    if (!ft_strncmp(node->full_cmd[0], ECHO, 4))
        do_echo(node);
    else if (!ft_strncmp(node->full_cmd[0], EXIT, 4))
        do_exit(struc);
    // else if (!ft_strcmp(node->full_cmd, CD))
    //     do_cd(node);
    // else if (!ft_strcmp(node->full_cmd, PWD))
    //     do_pwd(node);
    // else if (!ft_strcmp(node->full_cmd, ENV))
    //     do_env(node);
    // else if (!ft_strcmp(node->full_cmd, EXPORT))
    //     do_export(node);
    // else if (!ft_strcmp(node->full_cmd, UNSET))
    //     do_unset(node);
    else
        printf("Right now command is unknown!\n");
    return (0);
}