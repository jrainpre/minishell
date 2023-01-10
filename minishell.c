/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 08:06:40 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/10 09:58:34 by mkoller          ###   ########.fr       */
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

int count_pipes(char **split)
{
    int count;
    int i;
    
    i = 0;
    count = 0;
    while (split[i])
    {
        if (split[i][0] == '|')
            count++;
        i++;
    }
    return count;
}

void free_prompt(t_prompt *struc)
{
    t_parse *head;
    t_parse *help;

    head = struc->cmds;
    help = head;
    while (help)
    {
        free(help->full_cmd);
        help = help->next;
    }
    help = head->next;
    while (head)
    {
        if (head)
            free(head);
        head = help;
        if (help)
            help = help->next;
    }
    head = NULL;
    help = NULL;
}

void init_node(t_parse *node)
{
    node->full_cmd = NULL;
    node->full_path = NULL;
    node->next = NULL;
    node->in = 0;
    node->out = 0;
}

void add_nodes(t_prompt *struc, int ammount)
{
    t_parse *node;
    t_parse *head;
    int i;
    int first;
    
    first = 0;
    i = ammount;
    while (i >= 0)
    {
        node = malloc(sizeof(t_parse));
        init_node(node);
        if(first == 0)
        {
            struc->cmds = node;
            head = struc->cmds;
            first++;
        }
        else
        {
            head->next = node;
            head = head->next;
        }  
        i--;
    }
    node = NULL;
}

int put_to_table(char **str, t_prompt *struc)
{
    int i;
    int j;
    int count;
    t_parse *temp;

    count = count_pipes(str);
    i = 0;
    j = 0;
    add_nodes(struc, count);
    temp = struc->cmds;
    temp->full_cmd = malloc(100);
    while (str[i])
    {
        if (str[i][0] != '|')
        {
            temp->full_cmd[j] = str[i];
            j++;
            i++;
        }
        else if (str[i][0] == '|')
        {
            temp = temp->next;
            if (temp != NULL)
                temp->full_cmd = malloc(100);
            i++;
            j = 0;
        }
    }
    return (0);
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

void init_prompt(t_prompt *struc, char **env)
{
    struc->cmds = NULL;
    struc->envp = env;
    struc->pid = 0;
}

char** copie_env(char **env)
{
    int i;
    int j;
    char **new_env;

    i = 0;
    j = 0;
    while (env[i])
        i++;
    new_env = malloc(sizeof(char*) * (i + 1));
    while (j < i)
    {
        new_env[j] = ft_strjoin(env[j], "\0");
        j++;
    }
    new_env[j] = NULL;
    return (new_env);
}

int main(int argc, char **argv, char **envp)
{
    int i = 0;
    t_input input;
    t_prompt struc;
    t_parse *temp;
    
    init_prompt(&struc, copie_env(envp));
    temp = NULL;
    (void)argc;
	(void)argv;
    (void)envp;
   
    while (1)
    {
        input.c = ' ';
        input.str = readline("minishell $> ");
        add_history(input.str);
        ft_split_input(&input);
        put_to_table(input.output, &struc);
        temp = struc.cmds;
        while (temp)
        {
            printf("\nFull cmd: ");
            while (temp->full_cmd[i])
            {
                printf("%s ", temp->full_cmd[i]);
                i++;
            }
            printf("\nFull path: %s\n", temp->full_path);
            printf("In: %d\n", temp->in);
            printf("Out: %d\n", temp->out);
            printf("\n");
            temp = temp->next;
            i = 0;
        }
        free_prompt(&struc);
        free_input_output(&input);
        i = 0;
    }
    return(0);
}