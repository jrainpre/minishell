/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:57:02 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/25 11:09:27 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strisnum(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	do_exit(t_prompt *struc, t_parse *node)
{
	struc->exit_flag = 1;
	ft_putstr_fd("exit\n", 2);
	if (node->full_cmd[1] && node->full_cmd[2])
	{
		struc->exit_return_val = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	else if (node->full_cmd[1] && ft_strisnum(node->full_cmd[1]) == 0)
	{
		struc->exit_return_val = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(node->full_cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (node->full_cmd[1])
		struc->exit_return_val = ft_atoi(node->full_cmd[1]);
	else
		struc->exit_return_val = 0;
}
