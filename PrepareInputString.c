/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrepareInputString.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 09:40:41 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 09:04:29 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*this function checks if there are any pipes or redirects in the input string
 and if there are, it adds a space before them
  and if its a pipe also after them*/

int prepare_input_string_do(char *str, int *i)
{
	if (check_lastpos_is_space(str, *i))
	{
		str = add_space_before_this_position(str, i);
		return (1);
	}
	if (check_nextpos_is_space(str, *i))
	{
		str = add_space_after_this_position(str, i);
		return (1);
	}
	return (0);
}

char	*prepare_input_string(char *str)
{
	int	in_s_q;
	int	in_d_q;
	int	i;
	char *temp;
	temp = str;

	i = -1;
	in_s_q = 0;
	in_d_q = 0;
	while (str[++i] != '\0')
	{
		check_if_qoute(&in_s_q, &in_d_q, str[i]);
		if (check_if_unquoted_special_char(str, i, &in_s_q, &in_d_q))
		{
			if (prepare_input_string_do(str, &i) == 1)
				continue;
		}
	}
	return (str);
}

int	check_lastpos_is_space(char *str, int i)
{
	if ((i != 0 && str[i - 1] != ' ' &&
			str[i - 1] != '<' && str[i - 1] != '>'))
		return (1);
	return (0);
}

int	check_nextpos_is_space(char *str, int i)
{
	if (i != 0 && str[i] == '|' && str[i + 1] != ' ' &&
		str[i + 1] != '<' && str[i + 1] != '>')
		return (1);
	return (0);
}

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
		if ((!*s_q || !ft_strchr(&str[i + 1], '\'')) && (!*d_q
					|| !ft_strchr(&str[i + 1], '"')))
			return (1);
	}
	return (0);
}
