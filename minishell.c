/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 08:06:40 by mkoller           #+#    #+#             */
/*   Updated: 2022/12/19 15:47:37 by mkoller          ###   ########.fr       */
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
    
    (void)argc;
	(void)argv;
    (void)envp;
    table = malloc(sizeof(t_com));
    table->arguments = malloc(sizeof(t_parse_com) * 100);
    input.str= malloc(100);
    
    input.str = readline("minishell $> ");
    ft_split_input(&input);
    put_to_table(input.output, table);
    
    while (i < 2)
    {
        printf("Command: %s, ", table->arguments[i].command);
        printf("Flags: %s, ", table->arguments[i].flag);
        printf("In: %s, ", table->arguments[i].redir.in);
        printf("Out: %s", table->arguments[i].redir.out);
        printf("\n");
        i++;
    }
}