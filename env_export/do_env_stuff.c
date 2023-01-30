/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:54:18 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 14:15:55 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

int	do_unset(t_parse *node)
{
	int	i;

	g_global.exit_status = 0;
	i = 1;
	while (node->full_cmd[i])
	{
		delete_env_value(node->env, node->full_cmd[i]);
		i++;
	}
	return (0);
}

int	do_export(t_parse *node)
{
	int	saved;

	g_global.exit_status = 0;
	saved = 1;
	if (node->out >= 3)
	{
		saved = dup(STDOUT_FILENO);
		check_dup_out(node);
		export(node);
		restore_stdout(saved);
	}
	else
		export(node);
	return (0);
}

int	do_env(t_parse *node)
{
	int	saved;

	g_global.exit_status = 0;
	saved = 1;
	if (node->out >= 3)
	{
		saved = dup(STDOUT_FILENO);
		check_dup_out(node);
		print_env_list(node->env);
		restore_stdout(saved);
	}
	else
		print_env_list(node->env);
	return (0);
}
