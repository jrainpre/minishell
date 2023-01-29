#/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 08:06:40 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/27 09:45:44 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

t_global g_global;

int	count_pipes(char **split)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (split[i])
	{
		if (split[i][0] == '|')
			count++;
		i++;
	}
	return (count);
}

int	count_redirect(char **split)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (split[i])
	{
		if (split[i][0] == '>' || split[i][0] == '<')
			count++;
		i++;
	}
	return (count);
}

void	free_prompt(t_prompt *struc)
{
	int		i;
	t_parse	*head;
	t_parse	*help;

	i = 0;
	head = struc->cmds;
	help = head;
	while (help)
	{
		free_table(help->full_cmd);
		free(help->full_path);
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

void	init_node(t_parse *node)
{
	node->full_cmd = NULL;
	node->full_path = NULL;
	node->heredoc = NULL;
	node->env = NULL;
	node->next = NULL;
	node->in = STDIN_FILENO;
	node->out = STDOUT_FILENO;
}

void	add_nodes(t_prompt *struc, int ammount)
{
	t_parse	*node;
	t_parse	*head;
	int		i;
	int		first;

	first = 0;
	i = ammount;
	while (i >= 0)
	{
		node = malloc(sizeof(t_parse) + 1);
		init_node(node);
		if (first == 0)
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

int	pointer_count(char **str, int *i)
{
	int	count;

	count = 0;
	while (str[*i] && str[*i][0] != '|')
	{
		count++;
		*i += 1;
	}
	*i += 1;
	return (count);
}

int	put_to_table(char **str, t_prompt *struc)
{
	int		i;
	int		j;
	int		k;
	int		count;
	t_parse	*temp;

	count = count_pipes(str);
	i = 0;
	j = 0;
	k = 0;
	add_nodes(struc, count);
	temp = struc->cmds;
	temp->full_cmd = ft_calloc((pointer_count(str, &k) + 1), sizeof(char *));
	while (str[i])
	{
		if (str[i][0] != '|')
		{
			temp->full_cmd[j] = ft_strdup(str[i]);
			j++;
			i++;
		}
		else if (str[i][0] == '|')
		{
			temp = temp->next;
			if (temp != NULL)
				temp->full_cmd = ft_calloc((pointer_count(str, &k) + 1), sizeof(char *));
			i++;
			j = 0;
		}
	}
	return (0);
}

void	init_prompt(t_prompt *struc, t_env_list *env_lst)
{
	struc->cmds = NULL;
	struc->env_lst = env_lst;
	struc->pid = 0;
	struc->exit_flag = 0;
}

char	**copie_env(char **env)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	while (j < i)
	{
		new_env[j] = ft_strjoin(env[j], "\0");
		j++;
	}
	new_env[j] = NULL;
	return (new_env);
}

void	free_table(char **table)
{
	int	i;

	i = 0;
	if (table != NULL)
	{
		while (table[i])
		{
			free(table[i]);
			table[i] = NULL;
			i++;
		}
		free(table);
		table = NULL;
	}
}

char	**trim_2d_array(char **table)
{
	int		i;
	int		j;
	int		k;
	char	**new_table;

	i = 0;
	j = 0;
	k = 0;
	while (table[i])
		i++;
	new_table = malloc(sizeof(char *) * (i + 1));
	while (table[j])
	{
		if (table[j][0] != '\0')
		{
			new_table[k] = ft_strdup(table[j]);
			k++;
		}
		j++;
	}
	free_table(table);
	new_table[k] = NULL;
	return (new_table);
}

void clean_interrupt(t_prompt *struc, t_env_list *env_lst, t_input *input)
{
	unlink(".tmp");
	free(input->str);
	free_env_lst(env_lst);
}

void clean_exit(t_prompt *struc, t_input *input)
{
	unlink(".tmp");
	free_prompt(struc);
	free(input->str);
	free_table(input->output);
	free_env_lst(struc->env_lst);
}

void clean_loop(t_prompt *struc, t_input *input)
{
	unlink(".tmp");
	free_prompt(struc);
	free(input->str);
	free_table(input->output);
}

void	check_exit_flag(t_prompt *struc, t_input *input)
{
	if (struc->exit_flag == 1)
	{
		clean_exit(struc, input);
		exit(0);
	}
}

void	set_env_lst(t_env_list *env_lst, t_parse *temp, t_prompt *struc)
{
	t_parse	*temp2;

	temp = struc->cmds;
	temp->full_cmd = trim_2d_array(temp->full_cmd);
	temp->env = env_lst;
	temp2 = temp;
	while (temp2)
	{
		temp2->env = env_lst;
		temp2 = temp2->next;
	}
}



int	main(int argc, char **argv, char **envp)
{
	t_input		input;
	t_prompt	struc;
	t_parse		*node;
	t_env_list	*env_lst;

	(void)argc;
	(void)argv;
	(void)envp;
	fill_env_lst(&env_lst, envp);
	init_prompt(&struc, env_lst);
	shell_level_plus_one(&struc);
  	minishell(&struc, struc.cmds, env_lst);
	return (0);
}


int read_line_take_input(t_prompt *struc, t_parse *node, t_env_list *env_lst, t_input *input)
{
		run_signals(1);
		input->str = readline(PROMPT);
		if (!input->str)
		{
			clean_interrupt(struc, env_lst, input);
			run_signals(3);
		}
		if (ft_is_whitespace(input->str[0]))
			return(1);
		input->str = prepare_input_string(input->str);
		add_history(input->str);
		ft_split_input(input);
		return (0);
}

int process_intput(t_prompt *struc, t_parse *node, t_env_list *env_lst, t_input *input)
{
	put_to_table(input->output, struc);
	set_env_lst(env_lst, struc->cmds, struc);
	include_env_struc(struc);
	expand_tilde_struc(struc);
	if (!get_all_fd_out(struc) || !get_all_fd_in(struc))
		return (1);
	delete_closed_quotes_struc(struc);
		return (0);
}

int minishell(t_prompt *struc, t_parse *node, t_env_list *env_lst)
{
	t_input		input;
	while (1)
	{
		if (read_line_take_input(struc, node, env_lst, &input))
			continue ;
		if (process_intput(struc, struc->cmds, env_lst, &input))
			{
				clean_loop(struc, &input);
				 continue ;
			}
		executer(struc->cmds, struc);
		check_exit_flag(struc, &input);
		clean_loop(struc, &input);
	}
}
