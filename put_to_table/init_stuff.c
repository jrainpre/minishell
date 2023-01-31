/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:39:35 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/31 10:24:22 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	init_prompt(t_prompt *struc, t_env_list *env_lst)
{
	struc->cmds = NULL;
	struc->env_lst = env_lst;
	struc->pid = 0;
	struc->exit_flag = 0;
}

void	free_heredoc(t_parse *cmds)
{
	t_parse	*head;
	t_parse	*help;

	head = cmds;
	help = head;
	while (help)
	{
		if (help->heredoc)
			free(help->heredoc);
		help = help->next;
	}
}
