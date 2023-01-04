/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_env_in_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 08:58:54 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/04 10:40:50 by jrainpre         ###   ########.fr       */
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

t_env_list *duplicate_list(t_env_list *env_lst)
{
	t_env_list *new;
	t_env_list *temp;
	t_env_list *head;

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
		{
			new->next = malloc(sizeof(t_env_list));
			new = new->next;
			new->name = ft_strdup(temp->name);
			new->value = ft_strdup(temp->value);
			new->next = NULL;
		}
		temp = temp->next;
	}
	return (head);
}

t_env_list *sort_list_alphabetically(t_env_list *env_lst)
{
	t_env_list *temp;
	t_env_list *head;
	char *temp_name;
	char *temp_value;

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

void print_env_list(t_env_list *env_lst)
{
	t_env_list *temp;

	temp = env_lst;
	while (temp)
	{
		printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
}

void print_export_list(t_env_list *env_lst)
{
	t_env_list *sort_copy;
	t_env_list *temp;

	sort_copy = duplicate_list(env_lst);
	sort_copy = sort_list_alphabetically(sort_copy);
	temp = sort_copy;
	while (temp)
	{
		printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
	free_env_lst(sort_copy);
}
	