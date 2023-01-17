/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_env_in_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 08:58:54 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/17 12:52:23 by jrainpre         ###   ########.fr       */
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

void	print_env_list(t_env_list *env_lst)
{
	t_env_list	*temp;

	temp = env_lst;
	while (temp)
	{
		printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
}

void	print_export_list(t_env_list *env_lst)
{
	t_env_list	*sort_copy;
	t_env_list	*temp;

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

int	is_valid_env(const char *env)
{
	int	i;

	i = 0;
	if (ft_isdigit(env[i]) == 1)
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0)
			return (0);
		i++;
	}
	if (env[i] != '=')
		return (2);
	return (1);
}

int	add_env_entry(t_env_list *env, char *str)
{
	t_env_list	*temp;
	char		*name;
	char		*value;

	temp = env;
	name = ft_substr(str, 0, ft_strchr(str, '=') - str);
	value = ft_strdup(ft_strchr(str, '=') + 1);
	while (temp->next)
		temp = temp->next;
	temp->next = malloc(sizeof(t_env_list));
	temp = temp->next;
	temp->name = name;
	temp->value = value;
	temp->next = NULL;
	return (1);
}
int	add_env_no_value(t_env_list *env, char *str)
{
	t_env_list	*temp;
	char		*name;
	char		*value;

	temp = env;
	name = ft_strdup(str);
	value = ft_strdup("\'\'");
	while (temp->next)
		temp = temp->next;
	temp->next = malloc(sizeof(t_env_list));
	temp = temp->next;
	temp->name = name;
	temp->value = value;
	temp->next = NULL;
	return (1);
}

int	export_env(t_env_list *env, char **args)
{
	int		i;
	char	*name;

	i = 0;
	while (args[i])
		i++;
	if (i == 0)
		print_export_list(env);
	else
	{
		i = -1;
		while (args[++i])
		{
			name = ft_substr(args[i], 0, ft_strchr(args[i], '=') - args[i]);
			if (is_valid_env(args[i]) == 0)
				printf(EXPORT_ERROR, args[i]);
			if (is_valid_env(args[i]) == 0)
				return (1);
			if (is_valid_env(args[i]) == 2)
				add_env_no_value(env, args[i]);
			else if (get_env_value(env, name) == NULL)
				add_env_entry(env, args[i]);
			else
				changevalue(env, args[i]);
			free(name);
		}
	}
}

int	export_helper(t_env_list *env, char **args)
{
	int		i;
	char	*name;

	name = NULL;
	i = 0;
	while (args[i])
	{
		name = ft_substr(args[i], 0, ft_strchr(args[i], '=') - args[i]);
		if (is_valid_env(args[i]) == 0)
		{
			printf(EXPORT_ERROR, args[i]);
			free(name);
			i++;
			continue ;
		}
		if (is_valid_env(args[i]) == 2)
			add_env_no_value(env, args[i]);
		else if (get_env_value(env, name) == NULL)
			add_env_entry(env, args[i]);
		else
			changevalue(env, args[i]);
		free(name);
		i++;
	}
}

int	export(t_parse *node)
{
	char *name;
	int i;

	i = 1;
	if (node->full_cmd[i] == NULL || node->full_cmd[i][0] == '\0')
		print_export_list(node->env);
	else
		export_helper(node->env, &node->full_cmd[i]);
	return (1);
}