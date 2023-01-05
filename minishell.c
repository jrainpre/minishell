/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 08:06:40 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/05 17:15:47 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

void init_node(t_com *node)
{
    node->command = NULL;
    node->flag = NULL;
    node->next = NULL;
    node->redir.error = NULL;
    node->redir.in = NULL;
    node->redir.out = NULL;
    node->redir.fd_out = 0;
    node->redir.fd_in = 0;
    node->redir.fd_error = 0;
}

int add_node(t_com *node)
{
    t_com *new;
    
    new = malloc(sizeof(t_com));
    if(!new)
        return(1);
    init_node(new);
    if (node->next == NULL)
        node->next = new;
    return (0); 
}

void free_list(t_com *head)
{
    t_com *help;
    
    while (head)
    {
        help = head->next;
        if (head)
            free(head);
        head = NULL;
        head = help;
    }
}

int put_to_table(char **str, t_com *head)
{
    int i;
    int k;
    int last_cmd;
    t_com *temp;

    k = 0;
    i = 0;
    last_cmd = 0;
    temp = head;
    while (str[i])
    {
        if (k > 0 && str[i][0] == '-')
            if (!temp->flag)
                temp->flag = ft_strjoin(str[i], "\0");
            else
                temp->flag = ft_strjoin(temp->flag, str[i]);
        else if (k > 0 && str[i][0] == '>')
            if (!temp->redir.out)
                temp->redir.out = ft_strjoin(str[i], "\0");
            else 
                temp->redir.out = ft_strjoin(temp->redir.out, str[i]);
        else if (k > 0 && str[i][0] == '<')
            if (!temp->redir.in)
                temp->redir.in = ft_strjoin(str[i], "\0");
            else
                temp->redir.in = ft_strjoin(temp->redir.in, str[i]);
        else 
        {
            temp->command = str[i];
            last_cmd = k;
            k++;
        }
        i++;
        if (temp->next == NULL)
            add_node(temp);
        temp = temp->next;
    }
    return(0);
}

void free_input_output(t_input *input)
{
    int i;
    
    i = 0;
    while (input->output[i])
    {
        free(input->output[i]);
        input->output[i] = NULL;
        i++;
    }
    free(input->output);
    input->output = NULL;
}

int main(int argc, char **argv, char **envp)
{
    int i = 0;
    t_input input;
    t_com *head;
    t_com *temp;
    
    (void)argc;
	(void)argv;
    (void)envp;
   
    while (1)
    {
        input.c = ' ';
        head = malloc(sizeof(t_com));
        init_node(head);
        temp = head;
        input.str = readline("minishell $> ");
        add_history(input.str);
        ft_split_input(&input);
        put_to_table(input.output, temp);
        while (temp->next)
        {
            printf("%s\n", temp->command);
            printf("%s\n", temp->flag);
            printf("%s\n", temp->redir.in);
            printf("%s\n", temp->redir.out);
            printf("\n");
            temp = temp->next;
        }
        if (temp != NULL)
        {
            printf("%s\n", temp->command);
            printf("%s\n", temp->flag);
            printf("%s\n", temp->redir.in);
            printf("%s\n", temp->redir.out);
        }
        free_list(head);
        free_input_output(&input);
        head = NULL;
        temp = NULL;
        i++;
    }
    return(0);
}