/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:42:05 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/19 14:08:31 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_not_in_d_quotes_inpos(char *str, int *double_q)
{
	if (*double_q == 0)
		return (1);
	else if (!ft_strchr(++str, '\"'))
		return(1);
	else
		return(0);
}

int check_not_in_s_quotes_inpos(char *str, int *single_q)
{
	if (*single_q == 0)
		return (1);
	else if (!ft_strchr(++str, '\''))
		return(1);
	else
		return(0);
}

int check_not_in_s_quotes(char *str, char *pos)
{
	int	i;
	int	in_s_q;
	int	in_d_q;

	i = -1;
	in_s_q = 0;
	in_d_q = 0;
	while(str[++i])
	{
		check_if_qoute(&in_s_q, &in_d_q, str[i]);
		if (&str[i] == pos)
		{
			if (check_not_in_s_quotes_inpos(&str[i], &in_s_q))
				return(1);
			else 
				return (0);
		}
	}
	return(0);
}

int check_not_in_d_quotes(char *str, char *pos)
{
	int	i;
	int	in_s_q;
	int	in_d_q;

	i = -1;
	in_s_q = 0;
	in_d_q = 0;
	while(str[++i])
	{
		check_if_qoute(&in_s_q, &in_d_q, str[i]);
		if (&str[i] == pos)
		{
			if (check_not_in_d_quotes_inpos(&str[i], &in_d_q))
				return(1);
			else 
				return (0);
		}
	}
	return(0);
}

int check_pos_not_in_quotes(char *str, char *pos)
{
	if (check_not_in_s_quotes(str, pos) && check_not_in_d_quotes(str, pos))
		return (1);
	else
		return (0);
}


char	*find_unquoted_tilde(char *str)
{
	int	i;
	int	in_s_q;
	int	in_d_q;

	i = -1;
	in_s_q = 0;
	in_d_q = 0;
	while (str[++i] != '\0')
	{
		if(str[i] == '~' && check_pos_not_in_quotes(str, &str[i]))
			return(&str[i]);
		
	}
	return (NULL);
}

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
	new = ft_calloc((get_new_strlen(str, envvar, ptr) + 1), 1);
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
		while (find_unquoted_tilde(node->full_cmd[i]))
		{
			tilde_pos = find_unquoted_tilde(node->full_cmd[i]);
			
			name = get_env_tilde_value(node->env);
			temp = node->full_cmd[i];
			node->full_cmd[i] = get_new_str_tilde(node->full_cmd[i], name, tilde_pos);
			free(temp);
			free(name);
		}
		i++;
	}
}
	