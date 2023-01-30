/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 08:58:54 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 17:12:18 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	sort_copy = duplicate_list(env_lst, NULL);
	sort_copy = sort_list_alphabetically(sort_copy);
	temp = sort_copy;
	while (temp)
	{
		ft_printf("declare -x %s=%s\n", temp->name, temp->value);
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
	value = ft_strdup("");
	while (temp->next)
		temp = temp->next;
	temp->next = malloc(sizeof(t_env_list));
	temp = temp->next;
	temp->name = name;
	temp->value = value;
	temp->next = NULL;
	return (1);
}
