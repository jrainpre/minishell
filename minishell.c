/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 08:06:40 by mkoller           #+#    #+#             */
/*   Updated: 2022/12/19 13:20:50 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

int check_valid_command(t_com *table)
{
    
}

t_parse_com *new_command()
{
    t_parse_com *temp;
    
    temp = malloc(sizeof(t_parse_com));
    if (!temp)
        printf("ERROR!");
    return temp;
}

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
    char **str;
    
    (void)argc;
	(void)argv;
    (void)envp;
    t_com *table;
    table = malloc(sizeof(t_com));
    table->arguments = malloc(sizeof(t_parse_com) * 100);
    str = malloc(100);
    
    str[0] = "env";
    str[1] = "-n";
    str[2] = "-n";
    str[3] = ">file1";
    str[4] = ">file2";
    str[5] = "<file3";
    str[6] = NULL;
    
    put_to_table(str, table);
    
    // while (i < table->numberOfArguments)
    // {
    //     printf("%s, ", table->arguments[i].command);
    //     printf("%s, ", table->arguments[i].flag);
    //     printf("%s, ", table->arguments[i].redir.in);
    //     printf("%s", table->arguments[i].redir.out);
    //     printf("\n");
    //     i++;
    // }

    printf("Command: %s, ", table->arguments[i].command);
    printf("Flag: %s, ", table->arguments[i].flag);
    printf("In: %s, ", table->arguments[i].redir.in);
    printf("Out: %s\n", table->arguments[i].redir.out);

    // i = 0;
    // while (envp[i])
    // {
    //     printf("%s", envp[i]);
    //     i++;
    // }
}