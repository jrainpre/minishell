/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check_and_execute.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:45:26 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 14:22:30 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

void	exec_cmd(t_parse *node, int to_fork)
{
	build_path(node);
	if (check_error(node))
		return ;
	else
	{
		run_signals(2);
		if (to_fork)
		{
			if (fork() == 0)
			{
				dup_fds(node);
				execve(node->full_path, node->full_cmd, \
				env_list_to_array(node->env));
			}
			wait(&g_global.exit_status);
		}
		else
		{
			dup_fds(node);
			execve(node->full_path, node->full_cmd, \
			env_list_to_array(node->env));
		}
	}
}

int	builtin(t_parse *node, t_prompt *struc)
{
	if (!ft_strncmp(node->full_cmd[0], ECHO, 4))
		do_echo(node);
	else if (!ft_strncmp(node->full_cmd[0], EXIT, 4))
		do_exit(struc, node);
	else if (!ft_strncmp(node->full_cmd[0], CD, 2))
		do_cd(node);
	else if (!ft_strncmp(node->full_cmd[0], PWD, 3))
		do_pwd(node);
	else if (!ft_strncmp(node->full_cmd[0], ENV, 3))
		do_env(node);
	else if (!ft_strncmp(node->full_cmd[0], EXPORT, 6))
		do_export(node);
	else if (!ft_strncmp(node->full_cmd[0], UNSET, 5))
		do_unset(node);
	return (0);
}

int	is_bultin(t_parse *node)
{
	if (!ft_strncmp(node->full_cmd[0], ECHO, 4))
		return (1);
	else if (!ft_strncmp(node->full_cmd[0], EXIT, 4))
		return (1);
	else if (!ft_strncmp(node->full_cmd[0], CD, 2))
		return (1);
	else if (!ft_strncmp(node->full_cmd[0], PWD, 3))
		return (1);
	else if (!ft_strncmp(node->full_cmd[0], ENV, 3))
		return (1);
	else if (!ft_strncmp(node->full_cmd[0], EXPORT, 6))
		return (1);
	else if (!ft_strncmp(node->full_cmd[0], UNSET, 5))
		return (1);
	else
		return (0);
}

void	cmd_exec(t_parse *node, t_prompt *struc, int to_fork)
{
	if (is_bultin(node))
		builtin(node, struc);
	else
		exec_cmd(node, to_fork);
}
