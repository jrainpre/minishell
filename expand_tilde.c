/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:42:05 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/20 13:54:01 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env_tilde_value(t_env_list *env)
{
	char *value;
	while (env)
	{
		if (ft_strcmp(env->name, "HOME") == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	value = getcwd(NULL, 0);
	return(value);
}

char	*get_new_str_tilde(char *str, char *envvar, char *ptr)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	new = ft_calloc((get_new_strlen_env(str, envvar, ptr) + 1), 1);
	while (str[i] != '\0' && &str[i] != ptr)
		i++;
	ft_strncpy(new, str, i);
	ft_strcpy(&new[i], envvar);
	j = i;
	i++;
	while (new[j])
		j++;
	ft_strcpy(&new[j], &str[i]);
	return (new);
}

void expand_tilde(t_parse *node)
{
	char	*tilde_pos;
	char	*name;
	char	*temp;
	int		i;

	i = 0;
	while (node->full_cmd[i])
	{
		while (find_unquoted_char(node->full_cmd[i], '~'))
		{
			tilde_pos = find_unquoted_char(node->full_cmd[i], '~');
			
			name = get_env_tilde_value(node->env);
			temp = node->full_cmd[i];
			node->full_cmd[i] = get_new_str_tilde(node->full_cmd[i], name, tilde_pos);
			free(temp);
			free(name);
		}
		i++;
	}
}
	