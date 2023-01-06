/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 08:06:40 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/06 11:34:18 by mkoller          ###   ########.fr       */
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
    node->word = NULL;
    node->pipe = NULL;
    node->redir = NULL;
    node->next = NULL;
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
    t_com *temp;

    i = 0;
    temp = head;
    while (str[i])
    {
        if (ft_strcmp(str[i], "<<") == 0 || ft_strcmp(str[i], ">>") == 0 || str[i][0] == '>' || str[i][0] == '<')
        {
            if (!temp->redir)
                temp->redir = ft_strjoin(str[i], "\0");
        }
        else if (str[i][0] == '|')
        {
            if (!temp->pipe)
                temp->pipe = ft_strjoin(str[i], "\0");
        }
        else
            temp->word = str[i];
        i++;
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
        while (temp->word != NULL || temp->pipe != NULL || temp->redir != NULL)
        {
            printf("Word: %s\n", temp->word);
            printf("Pipe: %s\n", temp->pipe);
            printf("Redir: %s\n", temp->redir);
            printf("\n");
            temp = temp->next;
        }
        free_list(head);
        free_input_output(&input);
        head = NULL;
        temp = NULL;
        i++;
    }
    return(0);
}