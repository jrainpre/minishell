/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_input_string_helper.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 09:40:41 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 16:29:32 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	prepare_input_string_do(char **str, int *i)
{
	if (check_lastpos_is_space(*str, *i))
	{
		*str = add_space_before_this_position(*str, i);
		return (1);
	}
	if (check_nextpos_is_space(*str, *i))
	{
		*str = add_space_after_this_position(*str, i);
		return (1);
	}
	return (0);
}

char	*prepare_input_string(char *str)
{
	int		in_s_q;
	int		in_d_q;
	int		i;
	char	*temp;

	temp = str;
	i = -1;
	in_s_q = 0;
	in_d_q = 0;
	while (str[++i] != '\0')
	{
		check_if_qoute(&in_s_q, &in_d_q, str[i]);
		if (check_if_unquoted_special_char(str, i, &in_s_q, &in_d_q))
		{
			if (prepare_input_string_do(&str, &i) == 1)
				continue ;
		}
	}
	return (str);
}

int	check_lastpos_is_space(char *str, int i)
{
	if ((i != 0 && str[i - 1] != ' ' \
		&& str[i - 1] != '<' && str[i - 1] != '>'))
		return (1);
	return (0);
}

int	check_nextpos_is_space(char *str, int i)
{
	if (i != 0 && str[i] == '|' && str[i + 1] != ' ' \
		&& str[i + 1] != '<' && str[i + 1] != '>')
		return (1);
	return (0);
}
