/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathanrainprechter <jonathanrainprech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:32:01 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/27 19:06:39 by jonathanrai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

int	not_dollar(char *arg, int i)
{
	if (&arg[i] != arg)
	{
		if (arg[i] == '$')
			return (0);
	}
	return (1);
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
				node->full_cmd[i] = get_new_str_exitstatus(node->full_cmd[i],
						ft_itoa(g_global.exit_status), dollar_pos);
				free(temp);
				break ;
			}
			name = get_env_name(dollar_pos, node->env);
			temp = node->full_cmd[i];
			node->full_cmd[i] = get_new_str_env(node->full_cmd[i], name,
					dollar_pos);
			free(temp);
		}
	}
}

void include_env_struc(t_prompt *struc)
{
	t_parse	*node;

	node = struc->cmds;
	while (node)
	{
		include_env_node(node);
		node = node->next;
	}
}

char	*get_new_str_env(char *str, char *envvar, char *ptr)
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
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '"' && not_dollar(ptr, i))
		i++;
	while (new[j])
		j++;
	ft_strcpy(&new[j], &str[i]);
	return (new);
}

int	get_new_strlen_env(char *str, char *value, char *ptr)
{
	int	i;

	i = 0;
	while (*str != '\0' && str != ptr)
	{
		str++;
		i++;
	}
	while (*str != '\0' && not_dollar(str, i))
		str++;
	while (*str != '\0')
	{
		str++;
		i++;
	}
	i += ft_strlen(value);
	return (i);
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
	env_name = calloc(i + 1, 1);
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
