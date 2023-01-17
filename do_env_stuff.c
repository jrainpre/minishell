/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:54:18 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/17 11:10:53 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int do_unset(t_parse *node)
{
	int i;
	
	i = 1;
	while (node->full_cmd[i])
	{
		delete_env_value(node->env, node->full_cmd[i]);
		i++;
	}
	return (0);
}

int do_export(t_parse *node)
{
    int i;
    int j;
    int len;
    int saved;
    
    j = 0;
    i = 1;
    saved = 1;
    while (node->out[j])
        {
            if (node->out[j] >= 3)
            {
                saved = dup(STDOUT_FILENO);
                check_dup(node, j);
				export(node);
                restore_stdout(saved);
            }
            else
                export(node);
			j++;
        }
    return (0);
}

int do_env(t_parse *node)
{
	int i;
	int j;
	int len;
	int saved;
	
	j = 0;
	i = 1;
	saved = 1;
		while (node->out[j])
		{
			if (node->out[j] >= 3)
			{
				saved = dup(STDOUT_FILENO);
				check_dup(node, j);
				print_env_list(node->env);
				restore_stdout(saved);
			}
			else
				print_env_list(node->env);
			j++;
		}
	return (0);
}