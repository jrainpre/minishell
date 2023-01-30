/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:34:28 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/30 09:01:13 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    do_parent(t_parse *node, int *fd, int *backup)
{
    wrapper_close(&fd[1]);
    if (*backup != STDIN_FILENO)
        wrapper_close(backup);
    *backup = fd[0];
}

void    do_child(t_parse *node, t_prompt *struc, int *fd, int *backup)
{
    wrapper_dup2(backup, STDIN_FILENO);
    if (node->next != NULL)
        wrapper_dup2(&fd[1], STDOUT_FILENO);
    wrapper_close(&fd[0]);
    cmd_exec(node, struc, 0);
    exit(0);
}
int    piper(t_parse *node, t_prompt *struc, int backup)
{
    int        fd[2];
    pid_t    pid;
    t_parse *temp;

        while (node != NULL)
        {
            run_signals(2);
            wrapper_pipe(fd);
            wrapper_fork(&pid);
            if (pid == 0)
                do_child(node, struc, fd, &backup);
            else
            {
                do_parent(node, fd, &backup);
                node = node->next;
            }
        }
        temp = struc->cmds;
        while (temp != 0)
        {
            wrapper_wait(NULL);
            temp = temp->next;
        }
        if (backup != STDIN_FILENO)
            wrapper_close(&backup);
    return (1);
}

void    executer(t_parse *node, t_prompt *struc)
{
    if (node->full_cmd[0])
    {
        if (node->next == NULL)
            cmd_exec(node, struc, 1);
        else
            piper(node, struc, STDIN_FILENO);
    }
}
