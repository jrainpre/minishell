/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_to_table_helper2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:36:05 by jrainpre          #+#    #+#             */
/*   Updated: 2023/02/13 10:41:49 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_exit_flag(t_prompt *struc, t_input *input)
{
	if (struc->exit_flag == 1)
	{
		clean_exit(struc, input);
		exit(struc->exit_return_val);
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
