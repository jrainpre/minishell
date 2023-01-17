/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 08:06:40 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/17 09:15:00 by jrainpre         ###   ########.fr       */
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

int count_redirect(char **split)
{
    int count;
    int i;
    
    i = 0;
    count = 0;
    while (split[i])
    {
        if (split[i][0] == '>' || split[i][0] == '<')
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
    node->in = malloc(sizeof(int));
    *node->in = 0;
    node->out = malloc(sizeof(int));
    *node->out = 1; 
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
    struc->exit_flag = 0;
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

char *find_user(char **envp)
{
    int i;
    char *str;

    i = 0;
    str = NULL;
    while (envp[i])
    {
        if (!ft_strncmp(envp[i], USER, 4))
        {
            str = ft_strdup(envp[i]);
            break;
        } 
        i++;
    }
    str = ft_substr(str, 5, (ft_strlen(str) - 5));
    return str;
}

char *user_prompt(char **envp)
{
    char *str;
    
    str = GREEN;
    str = ft_strjoin(str, find_user(envp));
    str = ft_strjoin(str, "@");
    str = ft_strjoin(str, PROMPT);
    str = ft_strjoin(str, WHITE);
    return str;
}

int main(int argc, char **argv, char **envp)
{
    int i = 0;
    t_input input;
    t_prompt struc;
    t_parse *temp;
    t_env_list *env_lst;
    
    init_prompt(&struc, copie_env(envp));
    fill_env_lst(&env_lst, envp);
    temp = NULL;
    (void)argc;
	(void)argv;
    (void)envp;
   
    while (1)
    {
        input.c = ' ';
        input.str = readline(user_prompt(envp));
        add_history(input.str);
        ft_split_input(&input);
        put_to_table(input.output, &struc);
        //check if builtin
        get_all_fd_out(&struc);
        get_all_fd_in(&struc);
        temp = struc.cmds;
        temp->env= env_lst;
        // fork();
        builtin(temp, &struc, envp);
        // while (temp)
        // {
        //     //////////////////////////////////////////////////////////////////
        //     printf("\nFull cmd: "); 
        //     while (temp->full_cmd[i])
        //     {
        //         printf("%s ", temp->full_cmd[i]);
        //         i++;
        //     }
        //     //////////////////////////////////////////////////////////////////
        //     printf("\nFull path: %s\n", temp->full_path);
        //     //////////////////////////////////////////////////////////////////
        //     i = 0;
        //     if (temp->in)
        //     {
        //         while (temp->in[i])
        //         {
        //             printf("In: %d\n", temp->in[i]);
        //             i++;
        //         }
        //     }
        //     else
        //         printf("In: %p\n", temp->in);
        //     //////////////////////////////////////////////////////////////////
        //     i = 0;
        //     if (temp->out)
        //     {
        //         while (temp->out[i])
        //         {
        //             printf("Out: %d\n", temp->out[i]);
        //             i++;
        //         }
        //     }
        //     else
        //         printf("Out: %p\n", temp->out);
        //     ////////////////////////////////////////////////////////////////////
        //     printf("\n");
        //     temp = temp->next;
        //     i = 0;
        // }
        // wait();
        if (struc.exit_flag == 1)
        {
            free_prompt(&struc);
            free_input_output(&input);
            break;
        }
        free_prompt(&struc);
        free_input_output(&input);
        i = 0;
    }
    return(0);
}