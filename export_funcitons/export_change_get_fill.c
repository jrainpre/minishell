/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_change_get_fill.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:51:47 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 14:05:46 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_env_lst(t_env_list **env_lst, char **envp)
{
	int			i;
	t_env_list	*temp;
	t_env_list	*new;

	i = 0;
	temp = *env_lst;
	while (envp[i])
	{
		new = malloc(sizeof(t_env_list));
		new->name = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		new->value = ft_substr(envp[i], ft_strchr(envp[i], '=') - envp[i] + 1,
				ft_strlen(envp[i]));
		new->next = NULL;
		if (i == 0)
			*env_lst = new;
		else
			temp->next = new;
		temp = new;
		i++;
	}
}

char	*get_env_value(t_env_list *env_lst, char *name)
{
	t_env_list	*temp;

	temp = env_lst;
	while (temp)
	{
		if (ft_strcmp(temp->name, name) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

int	changevalue(t_env_list *env_lst, char *name_value)
{
	t_env_list	*temp;
	char		*name;
	char		*value;

	temp = env_lst;
	name = ft_substr(name_value, 0, ft_strchr(name_value, '=') - name_value);
	value = ft_substr(name_value, ft_strchr(name_value, '=') - name_value + 1,
			ft_strlen(name_value));
	while (temp)
	{
		if (ft_strcmp(temp->name, name) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			free(name);
			free(value);
			return (1);
		}
		temp = temp->next;
	}
	free(name);
	free(value);
	return (0);
}
