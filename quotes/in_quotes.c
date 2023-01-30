/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 08:32:50 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 14:07:14 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_not_in_d_quotes(char *str, char *pos)
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
			if (check_not_in_d_quotes_inpos(&str[i], &in_d_q))
				return (1);
			else
				return (0);
		}
	}
	return (0);
}

int	check_pos_not_in_quotes(char *str, char *pos)
{
	if (check_not_in_s_quotes(str, pos) && check_not_in_d_quotes(str, pos))
		return (1);
	else
		return (0);
}

int	check_pos_not_in_quotes_test(char *str, char *pos)
{
	if (!check_not_in_d_quotes(str, pos))
		return (1);
	if (check_not_in_s_quotes(str, pos))
		return (1);
	else
		return (0);
}

char	*find_unquoted_char(char *str, char c)
{
	int	i;
	int	in_s_q;
	int	in_d_q;

	i = 0;
	in_s_q = 0;
	in_d_q = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c && check_pos_not_in_quotes(str, &str[i]))
			return (&str[i]);
		i++;
	}
	return (NULL);
}

char	*find_not_in_squoutes_char(char *str, char c)
{
	int	i;
	int	in_s_q;

	i = 0;
	in_s_q = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c && check_pos_not_in_quotes_test(str, &str[i]))
			return (&str[i]);
		i++;
	}
	return (NULL);
}
