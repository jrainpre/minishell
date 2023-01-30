/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:34:28 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/29 19:18:13 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    do_parent(t_parse *node, int *fd, int *backup)
{
    // wrapper_wait(NULL);
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
}

void    wait_loop(t_parse *temp)
{
    while (temp != 0)
    {
        wrapper_wait(NULL);
        temp = temp->next;
    }
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
        wait_loop(temp);
        if (backup != STDIN_FILENO)
            wrapper_close(&backup);
    return (1);
}

int    executer(t_parse *node, t_prompt *struc)
{

    if (node->next == NULL)
        cmd_exec(node, struc, 1);
    else
        piper(node, struc, STDIN_FILENO);
    return (1);
}




/*
int pipefunction (t_parse node, t_promptstruc, char **env)
{
    int fd[2];   // file descriptor for the pipe
    pid_t pid;   // process ID
    int backup = STDIN_FILENO; // backup file descriptor for input
    backup = STDIN_FILENO;
    while (node != NULL)
    {
        pipe(fd); // create the pipe
        if ((pid = fork()) == -1)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)// Child process
        {
            dup2(backup,
        STDIN_FILENO);// redirect input to previous command's output
            if (node->next != NULL)
                dup2(fd[1],
        STDOUT_FILENO);// redirect output to next command's input
            close(fd[0]); // close read end of the pipe
            builtin(node, struc, env);
            exit(1);
        }
        else
        {
            // Parent process
            wait(NULL); // wait for child process to finish
            close(fd[1]); // close write end of the pipe
            if (backup != STDIN_FILENO)
                close(backup); // close previous commands input
            backup = fd[0];
    // read end of the pipe becomes the input for next command
            node = node->next;
        }
    }
    if (backup != STDIN_FILENO)
    close(backup);
}*/