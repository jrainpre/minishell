/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:32:01 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/31 12:53:02 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

void	update_full_cmd(t_parse *node, char *name, char *dollar_pos, int *i)
{
	node->full_cmd[*i] = get_new_str_env(node->full_cmd[*i], name, dollar_pos);
}

void	include_env_node(t_parse *node)
{
	char	*dollar_pos;
	char	*name;
	char	*temp;
	int		i;

	i = -1;
	while (node->full_cmd[++i])
	{
		while (find_not_in_squoutes_char(node->full_cmd[i], '$'))
		{
			dollar_pos = find_not_in_squoutes_char(node->full_cmd[i], '$');
			if (dollar_pos[1] == '?')
			{
				temp = node->full_cmd[i];
				node->full_cmd[i] = get_new_str_exitstatus(node->full_cmd[i], \
				ft_itoa(g_global.exit_status), dollar_pos);
				free(temp);
				break ;
			}
			name = get_env_name(dollar_pos, node->env);
			temp = node->full_cmd[i];
			update_full_cmd(node, name, dollar_pos, &i);
			free(temp);
		}
	}
}

void	include_env_struc(t_prompt *struc)
{
	t_parse	*node;

	node = struc->cmds;
	while (node)
	{
		include_env_node(node);
		node = node->next;
	}
}

char	*get_env_name(char *arg, t_env_list *env_lst)
{
	int		i;
	char	*env_name;
	char	*env_val;

	i = 0;
	while (arg[i] && (arg[i] != ' ' && arg[i] != '\'' && arg[i] != '\"'
			&& not_dollar(arg, i)))
		i++;
	env_name = ft_calloc(i + 1, 1);
	arg++;
	i = 0;
	while (arg[i] && (arg[i] != ' ' && arg[i] != '\'' && arg[i] != '\"'
			&& not_dollar(arg, i)))
	{
		env_name[i] = arg[i];
		i++;
	}
	env_val = get_env_value(env_lst, env_name);
	if (!env_val)
		env_val = ft_calloc(1, 1);
	free(env_name);
	return (env_val);
}
