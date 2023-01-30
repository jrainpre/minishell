/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 08:58:54 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 14:16:50 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

int	export_env_helper(char *name, int *i, t_env_list *env, char **args)
{
	name = ft_substr(args[*i], 0, ft_strchr(args[*i], '=') - args[*i]);
	if (is_valid_env(args[*i]) == 0)
		printf(EXPORT_ERROR, args[*i]);
	if (is_valid_env(args[*i]) == 0)
		return (1);
	if (is_valid_env(args[*i]) == 2)
		add_env_no_value(env, args[*i]);
	else if (get_env_value(env, name) == NULL)
		add_env_entry(env, args[*i]);
	else
		changevalue(env, args[*i]);
	free(name);
	return (0);
}

int	export_env(t_env_list *env, char **args)
{
	int		i;
	char	*name;

	i = 0;
	name = NULL;
	while (args[i])
		i++;
	if (i == 0)
		print_export_list(env);
	else
	{
		i = -1;
		while (args[++i])
		{
			if (export_env_helper(name, &i, env, args) == 1)
				return (1);
		}
	}
	return (1);
}

void	export_not_valid(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	g_global.exit_status = 1;
}

int	export_helper(t_env_list *env, char **args)
{
	int		i;
	char	*name;

	name = NULL;
	i = -1;
	while (args[++i])
	{
		name = ft_substr(args[i], 0, ft_strchr(args[i], '=') - args[i]);
		if (is_valid_env(args[i]) == 0)
		{
			export_not_valid(args[i]);
			free(name);
			continue ;
		}
		if (is_valid_env(args[i]) == 2)
			add_env_no_value(env, args[i]);
		else if (get_env_value(env, name) == NULL)
			add_env_entry(env, args[i]);
		else
			changevalue(env, args[i]);
		free(name);
	}
	return (1);
}

int	export(t_parse *node)
{
	int		i;

	g_global.exit_status = 0;
	i = 1;
	if (node->full_cmd[i] == NULL || node->full_cmd[i][0] == '\0')
		print_export_list(node->env);
	else
		export_helper(node->env, &node->full_cmd[i]);
	return (1);
}
