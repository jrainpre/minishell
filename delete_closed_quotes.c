/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_closed_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathanrainprechter <jonathanrainprech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:10:27 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/27 18:41:12 by jonathanrai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_len_no_quotes(char *str)
{
	int	to_delete;
	int	i;
	int	d_quote;
	int	s_quote;

	i = 0;
	to_delete = 0;
	d_quote = 0;
	s_quote = 0;
	while (str && str[i])
	{
		if (check_not_in_d_quotes(str, &str[i]) && str[i] == '\'')
			s_quote = !s_quote;
		if (check_not_in_s_quotes(str, &str[i]) && str[i] == '\"')
			d_quote = !d_quote;
		if ((str[i] == '\"' && !s_quote) || (str[i] == '\'' && !d_quote))
			to_delete++;
		i++;
	}
	return (to_delete);
}

char	*delete_closed_quotes_str(char *str, int s_quotes, int d_quotes)
{
	int		to_delete;
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = 0;
	to_delete = new_len_no_quotes(str);
	new = ft_calloc((ft_strlen(str) - to_delete + 1), sizeof(char));
	if (!new)
		return (NULL);
	while (str[j])
	{
		if (check_not_in_d_quotes(str, &str[j]) && str[j] == '\'')
			s_quotes = !s_quotes;
		if (check_not_in_s_quotes(str, &str[j]) && str[j] == '\"')
			d_quotes = !d_quotes;
		if ((str[j] != '\"' || s_quotes) && (str[j] != '\'' || d_quotes)
				&& ++i >= 0)
			new[i] = str[j];
		j++;
	}
	return (new);
}

void	delete_closed_quotes_node(t_parse *node)
{
	int		i;
	char	*temp;

	i = 0;
	while (node->full_cmd[i])
	{
		temp = node->full_cmd[i];
		node->full_cmd[i] = delete_closed_quotes_str(node->full_cmd[i], 0, 0);
		i++;
		free(temp);
	}
}

void delete_closed_quotes_struc(t_prompt *struc)
{
	t_parse	*temp;

	temp = struc->cmds;
	while (temp)
	{
		delete_closed_quotes_node(temp);
		temp = temp->next;
	}
}