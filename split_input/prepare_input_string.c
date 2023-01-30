/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_input_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 09:40:41 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 14:07:33 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_qoute(int *single_q, int *double_q, char c)
{
	if (c == '\'')
	{
		*single_q = !*single_q;
		return (1);
	}
	else if (c == '\"')
	{
		*double_q = !*double_q;
		return (1);
	}
	return (0);
}

char	*add_space_before_this_position(char *str, int *index)
{
	char	*temp;
	int		j;
	int		i;

	i = *index;
	j = 0;
	temp = ft_calloc(ft_strlen(str) + 2, 1);
	while (j < i)
	{
		temp[j] = str[j];
		j++;
	}
	temp[j] = ' ';
	j++;
	while (str[j - 1] != '\0')
	{
		temp[j] = str[j - 1];
		j++;
	}
	free(str);
	*index = i - 1;
	return (temp);
}

char	*add_space_after_this_position(char *str, int *index)
{
	char	*temp;
	int		j;
	int		i;

	i = *index;
	j = 0;
	temp = ft_calloc(ft_strlen(str) + 2, 1);
	while (j <= i)
	{
		temp[j] = str[j];
		j++;
	}
	temp[j] = ' ';
	j++;
	while (str[j - 1] != '\0')
	{
		temp[j] = str[j - 1];
		j++;
	}
	free(str);
	*index = i - 1;
	return (temp);
}

int	check_if_unquoted_special_char(char *str, int j, int *s_q, int *d_q)
{
	int	i;

	i = j;
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
	{
		if ((!*s_q || !ft_strchr(&str[i + 1], '\'')) && (!*d_q \
			|| !ft_strchr(&str[i + 1], '"')))
			return (1);
	}
	return (0);
}
