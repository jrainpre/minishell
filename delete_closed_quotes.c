/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_closed_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:10:27 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/19 17:14:40 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*delete_char(char *str, int pos)
// {
// 	int	i;
// 	int	j;
// 	char *tmp;

// 	i = 0;
// 	j = 0;
// 	tmp = ft_calloc(ft_strlen(str) - 1, sizeof(char));
// 	while (str[i])
// 	{
// 		if (i != pos)
// 		{
// 			tmp[j] = str[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	tmp[j] = '\0';
// 	return (tmp);
// }

// int	get_str_index(char *str, char *pos)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (&str[i] == pos)
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }




// int get_new_strlen(char *str)
// {
// 	int i;
// 	int j;
// 	int in_s_q;
// 	int in_d_q;

// 	i = -1;
// 	j = 0;
// 	in_s_q = 0;
// 	in_d_q = 0;
// 	while (str[++i])
// 	{
// 		check_if_qoute(&in_s_q, &in_d_q, str[i]);
// 		if ((str[i] == '\'' && check_not_in_d_quotes_inpos(&str[i], &in_d_q)) ||
// 		 (str[i] == '\"' && check_not_in_s_quotes_inpos(&str[i], &in_s_q)))
// 		{
// 			j += 2;
// 			i++;
// 			while (str[i] != str[i - 1])
// 				i++;
// 		}
// 		else
// 			j++;
// 	}
// 	return (j);
// }


// void	delete_closed_quotes(t_parse *node)
// {
// 	int i;
// 	char *close;
// 	char *tmp;
// 	char *tmp2;
// 	int k;
		
// 	i = -1;
// 	while (node->full_cmd[++i])
// 	{
// 		k = -1;
// 		while (node->full_cmd[i][++k])
// 		{
// 			if ((node->full_cmd[i][k] == '\'' && check_not_in_d_quotes(node->full_cmd[i], &node->full_cmd[i][k])) ||
// 			 (node->full_cmd[i][k] == '\"' && check_not_in_s_quotes(node->full_cmd[i], &node->full_cmd[i][k])))
// 			{
// 				close = ft_strchr(&node->full_cmd[i][k + 1], node->full_cmd[i][k]);
// 				tmp = node->full_cmd[i];
// 				tmp2 = delete_char(node->full_cmd[i], k);
// 				node->full_cmd[i] = delete_char(tmp2,(get_str_index(tmp, close) - 1));
// 				free(tmp);
// 				free(tmp2);
// 			}
// 		}
// 	}
// }

int	new_len(char *str)
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

char	*ft_strtrim_all(char *str, int s_quotes, int d_quotes)
{
	int		to_delete;
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = 0;
	to_delete = new_len(str);
	new = ft_calloc((ft_strlen(str) - to_delete + 1), sizeof(char));
	if (!new)
		return (NULL);
	while (str[j])
	{
		if (check_not_in_d_quotes(str, &str[j]) && str[j] == '\'')
			s_quotes = !s_quotes;
		if (check_not_in_s_quotes(str, &str[j]) && str[j] == '\"')
			d_quotes = !d_quotes;
		if ((str[j] != '\"' || s_quotes) && (str[j] != '\'' || d_quotes) \
			&& ++i >= 0)
			new[i] = str[j];
		j++;
	}
	return (new);
}


void delete_closed_quotes(t_parse *node)
{
	int i;
	char *temp;

	i = 0;
	while (node->full_cmd[i])
	{
		temp = node->full_cmd[i];
		node->full_cmd[i] = ft_strtrim_all(node->full_cmd[i], 0, 0);
		i++;
		free(temp);
	}
}