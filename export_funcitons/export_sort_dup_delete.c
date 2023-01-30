/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort_dup_delete.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:51:47 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 14:05:56 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	duplicate_list_helper(t_env_list *new, t_env_list *temp)
{
	new->next = malloc(sizeof(t_env_list));
	new = new->next;
	new->name = ft_strdup(temp->name);
	new->value = ft_strdup(temp->value);
	new->next = NULL;
}

t_env_list	*duplicate_list(t_env_list *env_lst)
{
	t_env_list	*new;
	t_env_list	*temp;
	t_env_list	*head;

	new = NULL;
	temp = env_lst;
	while (temp)
	{
		if (new == NULL)
		{
			new = malloc(sizeof(t_env_list));
			new->name = ft_strdup(temp->name);
			new->value = ft_strdup(temp->value);
			new->next = NULL;
			head = new;
		}
		else
			duplicate_list_helper(new, temp);
		temp = temp->next;
	}
	return (head);
}

t_env_list	*sort_list_alphabetically(t_env_list *env_lst)
{
	t_env_list	*temp;
	t_env_list	*head;
	char		*temp_name;
	char		*temp_value;

	head = env_lst;
	while (env_lst)
	{
		temp = env_lst->next;
		while (temp)
		{
			if (ft_strcmp(env_lst->name, temp->name) > 0)
			{
				temp_name = env_lst->name;
				temp_value = env_lst->value;
				env_lst->name = temp->name;
				env_lst->value = temp->value;
				temp->name = temp_name;
				temp->value = temp_value;
			}
			temp = temp->next;
		}
		env_lst = env_lst->next;
	}
	return (head);
}
