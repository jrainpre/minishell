/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_env_in_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 08:58:54 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/04 08:59:37 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	change_env_value(t_env_list *env_lst, char *name, char *value)
{
	t_env_list	*temp;

	temp = env_lst;
	while (temp)
	{
		if (ft_strcmp(temp->name, name) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			return ;
		}
		temp = temp->next;
	}
}

void	delete_env_value(t_env_list *env_lst, char *name)
{
	t_env_list	*temp;
	t_env_list	*prev;

	temp = env_lst;
	prev = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->name, name) == 0)
		{
			if (prev)
				prev->next = temp->next;
			else
				env_lst = temp->next;
			free(temp->name);
			free(temp->value);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

void	free_env_lst(t_env_list *env_lst)
{
	t_env_list	*temp;

	while (env_lst)
	{
		temp = env_lst;
		env_lst = env_lst->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}
