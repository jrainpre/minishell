/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_quotes_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 08:32:50 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 14:07:07 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_not_in_d_quotes_inpos(char *str, int *double_q)
{
	if (*double_q == 0)
		return (1);
	else if (!ft_strchr(++str, '\"'))
		return (1);
	else
		return (0);
}

int	check_not_in_s_quotes_inpos(char *str, int *single_q)
{
	if (*single_q == 0)
		return (1);
	else if (!ft_strchr(++str, '\''))
		return (1);
	else
		return (0);
}

int	check_not_in_s_quotes(char *str, char *pos)
{
	int	i;
	int	in_s_q;
	int	in_d_q;

	i = -1;
	in_s_q = 0;
	in_d_q = 0;
	while (str[++i])
	{
		check_if_qoute(&in_s_q, &in_d_q, str[i]);
		if (&str[i] == pos)
		{
			if (check_not_in_s_quotes_inpos(&str[i], &in_s_q))
				return (1);
			else
				return (0);
		}
	}
	return (0);
}
