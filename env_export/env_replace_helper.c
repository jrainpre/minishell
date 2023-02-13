/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:12:31 by jrainpre          #+#    #+#             */
/*   Updated: 2023/02/13 11:52:01 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	not_dollar(char *arg, int i)
{
	if (&arg[i] != arg)
	{
		if (arg[i] == '$')
			return (0);
	}
	return (1);
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
	while (!is_end_of_env(str[i], ptr, i, str))
		i++;
	while (new[j])
		j++;
	ft_strcpy(&new[j], &str[i]);
	return (new);
}

int	is_end_of_env(char c, char *ptr, int i, char *str)
{
	if (c == ' ' || c == '\0' || c == '"' || c == '\'' || \
	(c == '$' && &str[i] != ptr))
		return (1);
	return (0);
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
	while (*str != '\0' && (*str == '$' && str != ptr))
		str++;
	while (*str != '\0')
	{
		str++;
		i++;
	}
	i += ft_strlen(value);
	return (i);
}
