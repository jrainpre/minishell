/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 08:06:40 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/04 16:49:19 by jrainpre         ###   ########.fr       */
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

int put_to_table(char **str, t_com *table)
{
    int i;
    int k;
    int last_cmd;

    k = 0;
    i = 0;
    last_cmd = 0;
    while (str[i])
    {
        if (k > 0 && str[i][0] == '-')
            if (!table->arguments[last_cmd].flag)
                table->arguments[last_cmd].flag = ft_strjoin(str[i], "\0");
            else
                table->arguments[last_cmd].flag = ft_strjoin(table->arguments[last_cmd].flag, str[i]);
        else if (k > 0 && str[i][0] == '>')
            if (!table->arguments[last_cmd].redir.out)
                table->arguments[last_cmd].redir.out = ft_strjoin(str[i], "\0");
            else 
                table->arguments[last_cmd].redir.out = ft_strjoin(table->arguments[last_cmd].redir.out, str[i]);
        else if (k > 0 && str[i][0] == '<')
            if (!table->arguments[last_cmd].redir.in)
                table->arguments[last_cmd].redir.in = ft_strjoin(str[i], "\0");
            else
                table->arguments[last_cmd].redir.in = ft_strjoin(table->arguments[last_cmd].redir.in, str[i]);
        else 
        {
            table->arguments[k].command = str[i];
            table->numberOfArguments++;
            last_cmd = k;
            k++;
        }
        i++;
    }
    return (0);
}

int main(int argc, char *argv[], char **envp)
{
    int i = 0;
    t_input input;
    t_com *table;
    t_env_list *env_lst;
    
    (void)argc;
	(void)argv;
    (void)envp;
    
    // env_lst = NULL;
     fill_env_lst(&env_lst, envp);
         char *str[3];
    str[0] = "Hallo=99";
    str[1] = "Test=123";
    str[2] = NULL;
    export_env(env_lst, str);
//    delete_env_value(env_lst, "Hallo");

        str[0] = "Hallo=asdfasdf";
    str[1] = "Test=super";
    str[2] = NULL;
    export_env(env_lst, str);
        str[0] = NULL;
        export_env(env_lst, str);
    
    table = malloc(sizeof(t_com));
    table->arguments = malloc(sizeof(t_parse_com) * 100);
    input.str= malloc(100);
    input.c = ' ';
    input.str = readline("minishell $> ");
    ft_split_input(&input);
    include_env(&input, env_lst);
    // print_export_list(env_lst);
    put_to_table(input.output, table);

        // print_export_list(env_lst);

    while (i < 2)
    {
        printf("Command: %s, ", table->arguments[i].command);
        printf("Flags: %s, ", table->arguments[i].flag);
        printf("In: %s, ", table->arguments[i].redir.in);
        printf("Out: %s", table->arguments[i].redir.out);
        printf("\n");
        i++;
    }

    // while (envp[i])
    // {
    //     printf("%s\n", envp[i]);
    //     i++;
    // }

    
       free_env_lst(env_lst); 
}