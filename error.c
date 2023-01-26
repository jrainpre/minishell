/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 09:22:06 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/26 13:19:00 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_error(t_parse *node)
{
	if (node->full_path == NULL)
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
		return (1);
	}
	else if (node->full_cmd[0] == NULL)
	{
		put_error("minishell: command not found");
		return (1);
	}
	else 
		return (0);
}

void	put_error(char *str)
{
	ft_putstr_fd(str, 2);
}
