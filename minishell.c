/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 08:06:40 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/31 10:04:53 by mkoller          ###   ########.fr       */
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

t_global	g_global;

int	main(int argc, char **argv, char **envp)
{
	t_prompt	struc;
	t_env_list	*env_lst;

	(void)argc;
	(void)argv;
	(void)envp;
	fill_env_lst(&env_lst, envp);
	init_prompt(&struc, env_lst);
	shell_level_plus_one(&struc);
	minishell(&struc, env_lst);
	return (0);
}

int	read_line_take_input(t_env_list *env_lst,
		t_input *input, t_prompt *struc)
{
	run_signals(1);
	input->str = readline(PROMPT);
	if (!input->str)
	{
		clean_interrupt(env_lst, input, struc);
		run_signals(3);
	}
	if (ft_is_whitespace(input->str[0]))
		return (1);
	input->str = prepare_input_string(input->str);
	add_history(input->str);
	ft_split_input(input);
	return (0);
}

int	process_intput(t_prompt *struc, t_env_list *env_lst,
		t_input *input)
{
	put_to_table(input->output, struc);
	set_env_lst(env_lst, struc->cmds, struc);
	include_env_struc(struc);
	expand_tilde_struc(struc);
	if (!get_all_fd_out(struc) || !get_all_fd_in(struc))
		return (1);
	delete_closed_quotes_struc(struc);
	trim_nodes(struc);
	struc->input = input;
	return (0);
}

int	minishell(t_prompt *struc, t_env_list *env_lst)
{
	t_input	input;

	while (1)
	{
		if (read_line_take_input(env_lst, &input, struc))
			continue ;
		if (process_intput(struc, env_lst, &input))
		{
			clean_loop(struc, &input);
			continue ;
		}
		executer(struc->cmds, struc);
		check_exit_flag(struc, &input);
		clean_loop(struc, &input);
	}
}
