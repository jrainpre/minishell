/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 09:22:06 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/30 11:24:43 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	error_command_not_found(t_parse *node)
{
	if (node->full_cmd[0])
	{
		put_error(node->full_cmd[0]);
		put_error(": command not found");
		put_error("\n");
	}
	else
	{
		put_error("minishell: command not found");
		put_error("\n");
	}
}

int	check_error(t_parse *node)
{
	if (node->full_path == NULL)
	{
		error_command_not_found(node);
		g_global.exit_status = 127;
		return (1);
	}
	else if (node->full_cmd[0] == NULL)
	{
		put_error("minishell: command not found");
		g_global.exit_status = 127;
		return (1);
	}
	else if (error_message(node->full_path) != 0)
	{
		g_global.exit_status = 127;
		return (1);
	}
	return (0);
}

void	put_error(char *str)
{
	ft_putstr_fd(str, 2);
	g_global.exit_status = 127;
}
