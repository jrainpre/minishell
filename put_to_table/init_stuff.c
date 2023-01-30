/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:39:35 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 14:06:27 by jrainpre         ###   ########.fr       */
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
